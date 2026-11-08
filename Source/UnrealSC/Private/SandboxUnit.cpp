#include "SandboxUnit.h"

#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/StaticMesh.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"

ASandboxUnit::ASandboxUnit()
{
    PrimaryActorTick.bCanEverTick = true;

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    RootComponent = VisualMesh;
    VisualMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    VisualMesh->SetCollisionObjectType(ECC_WorldDynamic);
    VisualMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        VisualMesh->SetStaticMesh(CubeMesh.Object);
    }

    Label = CreateDefaultSubobject<UTextRenderComponent>(TEXT("UnitLabel"));
    Label->SetupAttachment(RootComponent);
    Label->SetHorizontalAlignment(EHTA_Center);
    Label->SetWorldSize(40.0f);
    Label->SetRelativeLocation(FVector(0.0f, 0.0f, 115.0f));
    Label->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
}

void ASandboxUnit::InitializeUnit(int32 InUnitId, ESandboxUnitType InType)
{
    UnitId = InUnitId;
    UnitType = InType;
    const bool bMarine = IsPlayerControlled();
    VisualMesh->SetRelativeScale3D(bMarine
        ? FVector(0.6f, 0.6f, 0.7f)
        : FVector(0.8f, 0.5f, 0.45f));

    Label->SetText(bMarine ? FText::FromString(TEXT("MARINE"))
                           : FText::FromString(TEXT("ZERGLING")));
    Label->SetTextRenderColor(bMarine ? FColor(95, 190, 255) : FColor(255, 110, 100));
}

void ASandboxUnit::SetSelected(bool bInSelected)
{
    bSelected = bInSelected;
    const bool bMarine = IsPlayerControlled();
    Label->SetTextRenderColor(bSelected ? FColor::Green
        : (bMarine ? FColor(95, 190, 255) : FColor(255, 110, 100)));
}

void ASandboxUnit::SetMockMoveTarget(const FVector& InWorldTarget)
{
    if (!IsPlayerControlled())
    {
        return;
    }
    MockMoveTarget = FVector(InWorldTarget.X, InWorldTarget.Y, GetActorLocation().Z);
    bHasMockMoveTarget = true;
}

void ASandboxUnit::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bHasMockMoveTarget)
    {
        const FVector Next = FMath::VInterpConstantTo(
            GetActorLocation(), MockMoveTarget, DeltaSeconds, MockMovementSpeed);
        SetActorLocation(Next, false);
        if (FVector::DistSquared(Next, MockMoveTarget) < FMath::Square(2.0f))
        {
            bHasMockMoveTarget = false;
        }
    }

    if (bSelected && GetWorld())
    {
        DrawDebugCircle(GetWorld(), GetActorLocation() - FVector(0.0f, 0.0f, 30.0f),
            75.0f, 24, FColor::Green, false, 0.0f, 0, 3.0f,
            FVector(1.0f, 0.0f, 0.0f), FVector(0.0f, 1.0f, 0.0f), false);
    }
}
