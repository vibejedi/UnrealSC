#include "RTSGameMode.h"

#include "RTSCameraPawn.h"
#include "RTSPlayerController.h"
#include "CombatSandbox.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ARTSGameMode::ARTSGameMode()
{
    DefaultPawnClass = ARTSCameraPawn::StaticClass();
    PlayerControllerClass = ARTSPlayerController::StaticClass();
}

void ARTSGameMode::BeginPlay()
{
    Super::BeginPlay();

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    // A designer may place BP_CombatSandbox in the level and assign BP unit classes.
    // Avoid creating a second arena in that case.
    TArray<AActor*> ExistingSandboxes;
    UGameplayStatics::GetAllActorsOfClass(
        World, ACombatSandbox::StaticClass(), ExistingSandboxes);

    if (ExistingSandboxes.IsEmpty())
    {
        World->SpawnActor<ACombatSandbox>(
            ACombatSandbox::StaticClass(),
            FVector(0.0f, 0.0f, 10.0f),
            FRotator::ZeroRotator);
    }
}
