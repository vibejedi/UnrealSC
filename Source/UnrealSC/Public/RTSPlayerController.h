#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

class ASandboxUnit;

UCLASS()
class UNREALSC_API ARTSPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    ARTSPlayerController();
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    UPROPERTY()
    TObjectPtr<ASandboxUnit> SelectedUnit;

    void SelectUnderCursor();
    void IssueMockMoveUnderCursor();
};
