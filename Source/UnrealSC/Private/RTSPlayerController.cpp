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

    if (IsValid(SelectedUnit))
    {
        SelectedUnit->SetSelected(false);
    }
    SelectedUnit = nullptr;

    if (IsValid(HitUnit) && HitUnit->IsPlayerControlled() && HitUnit->IsAlive())
    {
        SelectedUnit = HitUnit;
        SelectedUnit->SetSelected(true);
    }
}

void ARTSPlayerController::IssueMockMoveUnderCursor()
{
    if (!IsValid(SelectedUnit) || !SelectedUnit->IsAlive())
    {
        return;
    }

    FHitResult Hit;
    if (!GetHitResultUnderCursor(ECC_Visibility, false, Hit))
    {
        return;
    }

    ASandboxUnit* HitUnit = Cast<ASandboxUnit>(Hit.GetActor());
    if (IsValid(HitUnit) && HitUnit->IsAlive() && !HitUnit->IsPlayerControlled())
    {
        SelectedUnit->SetMockAttackTarget(HitUnit);
    }
    else
    {
        // Temporary movement implementation; future orders go to OpenBW.
        SelectedUnit->SetMockMoveTarget(Hit.ImpactPoint);
    }
}
