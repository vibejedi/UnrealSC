#include "SandboxUnit.h"

#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ASandboxUnit::ASandboxUnit()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    RootComponent = SceneRoot;

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    VisualMesh->SetupAttachment(RootComponent);
    VisualMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    VisualMesh->SetCollisionObjectType(ECC_WorldDynamic);
    VisualMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
    VisualMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        VisualMesh->SetStaticMesh(CubeMesh.Object);
    }

    ArtMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArtMesh"));
    ArtMesh->SetupAttachment(RootComponent);
    ArtMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    ArtMesh->SetVisibility(false);

    Label = CreateDefaultSubobject<UTextRenderComponent>(TEXT("UnitLabel"));
    Label->SetupAttachment(RootComponent);
    Label->SetHorizontalAlignment(EHTA_Center);
    Label->SetWorldSize(38.0f);
    Label->SetRelativeLocation(FVector(0.0f, 0.0f, 230.0f));
}

void ASandboxUnit::BeginPlay()
{
    Super::BeginPlay();
    if (ArtMesh && ArtMesh->GetSkeletalMeshAsset())
    {
        VisualMesh->SetVisibility(false);
        ArtMesh->SetVisibility(true);
    }
}

void ASandboxUnit::InitializeUnit(int32 InUnitId, ESandboxUnitType InType)
{
    UnitId = InUnitId;
    UnitType = InType;
    bDead = false;

    // Intentional prototype values; NOT canonical Brood War statistics.
    if (IsPlayerControlled())
    {
        MaxHealth = 40.0f;
        MovementSpeed = 320.0f;
        AttackRange = 950.0f;
        SightRange = 1100.0f;
        Damage = 8.0f;
        AttackInterval = 0.68f;
        VisualMesh->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.7f));
        VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 35.0f));
        Label->SetRelativeLocation(FVector(0.0f, 0.0f, 260.0f));
    }
    else
    {
        MaxHealth = 35.0f;
        MovementSpeed = 500.0f;
        AttackRange = 130.0f;
        SightRange = 2500.0f;
        Damage = 5.0f;
        AttackInterval = 0.9f;
        VisualMesh->SetRelativeScale3D(FVector(0.8f, 0.5f, 0.45f));
        VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 22.5f));
        Label->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
    }

    Health = MaxHealth;
    CooldownRemaining = 0.15f + InUnitId * 0.03f;
    SearchRemaining = 0.1f + (InUnitId % 5) * 0.06f;
    RefreshLabel();
}

void ASandboxUnit::RefreshLabel()
{
    if (!Label)
    {
        return;
    }

    const FString Name = IsPlayerControlled() ? TEXT("MARINE") : TEXT("ZERGLING");
    const FString Title = bDead
        ? FString::Printf(TEXT("%s - DOWN"), *Name)
        : FString::Printf(TEXT("%s %d/%d"), *Name,
            FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));

    Label->SetText(FText::FromString(Title));
    const FColor Color = bDead ? FColor::Silver
        : HitFlashRemaining > 0.0f ? FColor::Yellow
        : bSelected ? FColor::Green
        : IsPlayerControlled() ? FColor(95, 190, 255)
        : FColor(255, 110, 100);
    Label->SetTextRenderColor(Color);
}

void ASandboxUnit::SetSelected(bool bInSelected)
{
    bSelected = bInSelected && !bDead;
    RefreshLabel();
}

void ASandboxUnit::SetMockMoveTarget(const FVector& InWorldTarget)
{
    if (!IsPlayerControlled() || bDead)
    {
        return;
    }

    MockMoveTarget = FVector(InWorldTarget.X, InWorldTarget.Y, GetActorLocation().Z);
    bHasMockMoveTarget = true;
    bExplicitAttackOrder = false;
    CurrentTarget.Reset();
    BP_OnMoveOrder(MockMoveTarget);
}

void ASandboxUnit::SetMockAttackTarget(ASandboxUnit* InTarget)
{
    if (!IsPlayerControlled() || bDead || !IsValid(InTarget) ||
        !InTarget->IsAlive() || InTarget->GetUnitType() == UnitType)
    {
        return;
    }

    CurrentTarget = InTarget;
    bExplicitAttackOrder = true;
    bHasMockMoveTarget = false;
}

void ASandboxUnit::FindNearestEnemy()
{
    UWorld* World = GetWorld();
    if (!World || bDead)
    {
        return;
    }

    TArray<AActor*> Actors;
    UGameplayStatics::GetAllActorsOfClass(World, ASandboxUnit::StaticClass(), Actors);
    ASandboxUnit* Best = nullptr;
    float BestDistanceSq = FMath::Square(SightRange);

    for (AActor* Actor : Actors)
    {
        ASandboxUnit* Candidate = Cast<ASandboxUnit>(Actor);
        if (!IsValid(Candidate) || Candidate == this || !Candidate->IsAlive() ||
            Candidate->GetUnitType() == UnitType)
        {
            continue;
        }

        const float DistanceSq = FVector::DistSquared2D(
            GetActorLocation(), Candidate->GetActorLocation());
        if (DistanceSq < BestDistanceSq)
        {
            Best = Candidate;
            BestDistanceSq = DistanceSq;
        }
    }

    CurrentTarget = Best;
}

void ASandboxUnit::MoveTowards(const FVector& Destination, float DeltaSeconds)
{
    const FVector From = GetActorLocation();
    const FVector To(Destination.X, Destination.Y, From.Z);
    const FVector Next = FMath::VInterpConstantTo(From, To,
        DeltaSeconds, MovementSpeed);
    SetActorLocation(Next, false);
    VisualMoveSpeed = DeltaSeconds > UE_SMALL_NUMBER
        ? FVector::Dist2D(From, Next) / DeltaSeconds : 0.0f;
    const FVector Delta = To - From;
    if (!Delta.IsNearlyZero())
    {
        SetActorRotation(FRotator(0.0f, Delta.Rotation().Yaw, 0.0f));
    }
}

void ASandboxUnit::Attack(ASandboxUnit* Target)
{
    if (!IsValid(Target) || !Target->IsAlive())
    {
        return;
    }

    BP_OnAttack(Target);

    // Temporary tracer for the presentation sandbox; replaced by authored VFX.
    if (IsPlayerControlled() && GetWorld())
    {
        const FVector Start = GetActorLocation() + FVector(0.0f, 0.0f, 115.0f);
        const FVector End = Target->GetActorLocation() + FVector(0.0f, 0.0f, 70.0f);
        DrawDebugLine(GetWorld(), Start, End, FColor(255, 215, 95),
            false, 0.12f, 0, 3.5f);
        DrawDebugSphere(GetWorld(), End, 28.0f, 8, FColor::Orange,
            false, 0.15f, 0, 2.0f);
    }

    Target->ReceiveMockDamage(Damage);
}

void ASandboxUnit::ReceiveMockDamage(float Amount)
{
    if (bDead || Amount <= 0.0f)
    {
        return;
    }

    Health = FMath::Max(0.0f, Health - Amount);
    HitFlashRemaining = 0.16f;
    RefreshLabel();
    BP_OnDamaged(Health, MaxHealth);

    if (Health <= 0.0f)
    {
        Die();
    }
}

void ASandboxUnit::Die()
{
    bDead = true;
    bSelected = false;
    bHasMockMoveTarget = false;
    CurrentTarget.Reset();

    VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    RefreshLabel();
    BP_OnDeath();
    SetLifeSpan(2.5f);
}

void ASandboxUnit::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    VisualMoveSpeed = 0.0f;
    if (bDead)
    {
        return;
    }

    CooldownRemaining = FMath::Max(0.0f, CooldownRemaining - DeltaSeconds);

    if (HitFlashRemaining > 0.0f)
    {
        HitFlashRemaining = FMath::Max(0.0f, HitFlashRemaining - DeltaSeconds);
        if (HitFlashRemaining == 0.0f)
        {
            RefreshLabel();
        }
    }

    ASandboxUnit* Target = CurrentTarget.Get();
    if (Target && (!IsValid(Target) || !Target->IsAlive()))
    {
        CurrentTarget.Reset();
        bExplicitAttackOrder = false;
        Target = nullptr;
    }

    SearchRemaining -= DeltaSeconds;
    if (SearchRemaining <= 0.0f)
    {
        SearchRemaining = 0.25f;
        if (!Target && (!IsPlayerControlled() || !bHasMockMoveTarget))
        {
            FindNearestEnemy();
            Target = CurrentTarget.Get();
        }
    }

    if (Target && IsValid(Target) && Target->IsAlive())
    {
        const FVector ToTarget = Target->GetActorLocation() - GetActorLocation();
        const float DistanceSq = ToTarget.SizeSquared2D();

        if (DistanceSq <= FMath::Square(AttackRange))
        {
            if (CooldownRemaining <= 0.0f)
            {
                SetActorRotation(FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f));
                Attack(Target);
                CooldownRemaining = AttackInterval;
            }
            if (bSelected && GetWorld())
            {
                DrawDebugCircle(GetWorld(), GetActorLocation() + FVector(0, 0, 6),
                    75.0f, 24, FColor::Green, false, 0.0f, 0, 3.0f,
                    FVector(1, 0, 0), FVector(0, 1, 0), false);
            }
            return;
        }

        if (!IsPlayerControlled() || bExplicitAttackOrder)
        {
            MoveTowards(Target->GetActorLocation(), DeltaSeconds);
        }
    }
    else if (bHasMockMoveTarget)
    {
        MoveTowards(MockMoveTarget, DeltaSeconds);
        if (FVector::DistSquared2D(GetActorLocation(), MockMoveTarget) < FMath::Square(8.0f))
        {
            bHasMockMoveTarget = false;
        }
    }

    if (bSelected && GetWorld())
    {
        DrawDebugCircle(GetWorld(), GetActorLocation() + FVector(0, 0, 6),
            75.0f, 24, FColor::Green, false, 0.0f, 0, 3.0f,
            FVector(1, 0, 0), FVector(0, 1, 0), false);
    }
}
