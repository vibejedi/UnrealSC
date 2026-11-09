#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatSandbox.generated.h"

class UStaticMeshComponent;
class ASandboxUnit;

/** Replaceable 5-v-8 combat test encounter, not authentic Brood War logic. */
UCLASS(Blueprintable)
class UNREALSC_API ACombatSandbox : public AActor
{
    GENERATED_BODY()

public:
    ACombatSandbox();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sandbox")
    TObjectPtr<UStaticMeshComponent> Ground;

    /** In a placed Blueprint subclass, set these to unit Blueprint classes. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sandbox|Art")
    TSubclassOf<ASandboxUnit> MarineClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sandbox|Art")
    TSubclassOf<ASandboxUnit> ZerglingClass;
};
