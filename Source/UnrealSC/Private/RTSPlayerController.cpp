#include "RTSPlayerController.h"

#include "SandboxUnit.h"
#include "Components/InputComponent.h"

ARTSPlayerController::ARTSPlayerController()
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
}

void ARTSPlayerController::BeginPlay()
{
    Super::BeginPlay();

    FInputModeGameAndUI Mode;
    Mode.SetHideCursorDuringCapture(false);
    SetInputMode(Mode);
}

void ARTSPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    check(InputComponent);
    InputComponent->BindAction(TEXT("RTSSelect"), IE_Pressed,
        this, &ARTSPlayerController::SelectUnderCursor);
    InputComponent->BindAction(TEXT("RTSMockMove"), IE_Pressed,
        this, &ARTSPlayerController::IssueMockMoveUnderCursor);
}

void ARTSPlayerController::SelectUnderCursor()
{
    FHitResult Hit;
    ASandboxUnit* HitUnit = nullptr;
    if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
    {
        HitUnit = Cast<ASandboxUnit>(Hit.GetActor());
    }

    if (SelectedUnit)
    {
        SelectedUnit->SetSelected(false);
        SelectedUnit = nullptr;
    }

    if (HitUnit && HitUnit->IsPlayerControlled())
    {
        SelectedUnit = HitUnit;
        SelectedUnit->SetSelected(true);
        UE_LOG(LogTemp, Log, TEXT("UnrealSC selected mock unit %d"),
            SelectedUnit->GetUnitId());
    }
}

void ARTSPlayerController::IssueMockMoveUnderCursor()
{
    if (!SelectedUnit)
    {
        return;
    }

    FHitResult Hit;
    if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
    {
        // Sandbox-only movement: the future OpenBW bridge will own commands and positions.
        SelectedUnit->SetMockMoveTarget(Hit.ImpactPoint);
    }
}
