#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatSandbox.generated.h"

class UStaticMeshComponent;

/** Spawns a temporary 3D test map with 5 Marines and 8 Zerglings. */
UCLASS()
class UNREALSC_API ACombatSandbox : public AActor
{
    GENERATED_BODY()

public:
    ACombatSandbox();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sandbox")
    TObjectPtr<UStaticMeshComponent> Ground;
};
