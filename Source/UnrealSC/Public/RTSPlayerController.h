#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

UCLASS()
class UNREALSC_API ARTSPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    ARTSPlayerController();
    virtual void BeginPlay() override;
};
