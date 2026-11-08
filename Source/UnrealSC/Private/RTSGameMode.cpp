#include "RTSGameMode.h"

#include "RTSCameraPawn.h"
#include "RTSPlayerController.h"
#include "CombatSandbox.h"
#include "Engine/World.h"

ARTSGameMode::ARTSGameMode()
{
    DefaultPawnClass = ARTSCameraPawn::StaticClass();
    PlayerControllerClass = ARTSPlayerController::StaticClass();
}

void ARTSGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Spawn the standalone sandbox in any basic empty test level.
    // No OpenBW simulation is active at this stage.
    if (UWorld* World = GetWorld())
    {
        World->SpawnActor<ACombatSandbox>(
            ACombatSandbox::StaticClass(),
            FVector(0.0f, 0.0f, 10.0f),
            FRotator::ZeroRotator);
    }
}
