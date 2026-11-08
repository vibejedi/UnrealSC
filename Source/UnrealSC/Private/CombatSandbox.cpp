#include "CombatSandbox.h"

#include "SandboxUnit.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

ACombatSandbox::ACombatSandbox()
{
    PrimaryActorTick.bCanEverTick = false;

    Ground = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ground"));
    RootComponent = Ground;
    Ground->SetRelativeScale3D(FVector(65.0f, 65.0f, 1.0f));
    Ground->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Ground->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("/Engine/BasicShapes/Plane.Plane"));
    if (PlaneMesh.Succeeded())
    {
        Ground->SetStaticMesh(PlaneMesh.Object);
    }
}

void ACombatSandbox::BeginPlay()
{
    Super::BeginPlay();

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    for (int32 Index = 0; Index < 5; ++Index)
    {
        const FVector Position(-800.0f, (Index - 2) * 230.0f, 80.0f);
        if (ASandboxUnit* Unit = World->SpawnActor<ASandboxUnit>(
                ASandboxUnit::StaticClass(), Position, FRotator::ZeroRotator, SpawnParams))
        {
            Unit->InitializeUnit(Index + 1, ESandboxUnitType::Marine);
        }
    }

    for (int32 Index = 0; Index < 8; ++Index)
    {
        const FVector Position(800.0f + (Index / 4) * 160.0f,
            (Index % 4) * 240.0f - 360.0f, 80.0f);
        if (ASandboxUnit* Unit = World->SpawnActor<ASandboxUnit>(
                ASandboxUnit::StaticClass(), Position, FRotator::ZeroRotator, SpawnParams))
        {
            Unit->InitializeUnit(100 + Index, ESandboxUnitType::Zergling);
        }
    }
}
