#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RTSGameMode.generated.h"

UCLASS()
class UNREALSC_API ARTSGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    ARTSGameMode();
    virtual void BeginPlay() override;
};
