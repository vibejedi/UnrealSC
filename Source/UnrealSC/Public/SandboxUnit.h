#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SandboxUnit.generated.h"

class UStaticMeshComponent;
class UTextRenderComponent;

UENUM(BlueprintType)
enum class ESandboxUnitType : uint8
{
    Marine,
    Zergling
};

/**
 * Temporary 3D representation for testing RTS input.
 * This actor is not the authoritative Brood War simulation.
 */
UCLASS()
class UNREALSC_API ASandboxUnit : public AActor
{
    GENERATED_BODY()

public:
    ASandboxUnit();
    virtual void Tick(float DeltaSeconds) override;

    void InitializeUnit(int32 InUnitId, ESandboxUnitType InType);
    void SetSelected(bool bInSelected);
    void SetMockMoveTarget(const FVector& InWorldTarget);

    bool IsPlayerControlled() const { return UnitType == ESandboxUnitType::Marine; }
    int32 GetUnitId() const { return UnitId; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sandbox")
    TObjectPtr<UStaticMeshComponent> VisualMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sandbox")
    TObjectPtr<UTextRenderComponent> Label;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sandbox")
    ESandboxUnitType UnitType = ESandboxUnitType::Marine;

private:
    int32 UnitId = INDEX_NONE;
    bool bSelected = false;
    bool bHasMockMoveTarget = false;
    FVector MockMoveTarget = FVector::ZeroVector;
    float MockMovementSpeed = 450.0f;
};
