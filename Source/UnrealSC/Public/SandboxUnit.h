#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SandboxUnit.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class UTextRenderComponent;

UENUM(BlueprintType)
enum class ESandboxUnitType : uint8
{
    Marine,
    Zergling
};

/**
 * Milestone 3 mock combat actor.
 *
 * IMPORTANT: This is replaceable sandbox combat, NOT Brood War / OpenBW logic.
 * Blueprint hooks and the optional ArtMesh let us develop high-quality
 * animation/VFX without tying our eventual simulation to Unreal physics.
 */
UCLASS(Blueprintable)
class UNREALSC_API ASandboxUnit : public AActor
{
    GENERATED_BODY()

public:
    ASandboxUnit();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    void InitializeUnit(int32 InUnitId, ESandboxUnitType InType);
    void SetSelected(bool bInSelected);
    void SetMockMoveTarget(const FVector& InWorldTarget);
    void SetMockAttackTarget(ASandboxUnit* InTarget);
    void ReceiveMockDamage(float Amount);

    UFUNCTION(BlueprintPure, Category="Sandbox|Combat")
    bool IsAlive() const { return !bDead; }

    UFUNCTION(BlueprintPure, Category="Sandbox|Combat")
    bool IsPlayerControlled() const { return UnitType == ESandboxUnitType::Marine; }

    UFUNCTION(BlueprintPure, Category="Sandbox|Combat")
    float GetHealthRatio() const { return MaxHealth > 0.0f ? Health / MaxHealth : 0.0f; }

    UFUNCTION(BlueprintPure, Category="Sandbox|Combat")
    int32 GetUnitId() const { return UnitId; }

    UFUNCTION(BlueprintPure, Category="Sandbox|Combat")
    ESandboxUnitType GetUnitType() const { return UnitType; }

    /** Implement in a Blueprint child when detailed animation and VFX are ready. */
    UFUNCTION(BlueprintImplementableEvent, Category="Sandbox|Presentation")
    void BP_OnAttack(ASandboxUnit* TargetUnit);

    UFUNCTION(BlueprintImplementableEvent, Category="Sandbox|Presentation")
    void BP_OnDamaged(float RemainingHealth, float TotalHealth);

    UFUNCTION(BlueprintImplementableEvent, Category="Sandbox|Presentation")
    void BP_OnDeath();

    UFUNCTION(BlueprintImplementableEvent, Category="Sandbox|Presentation")
    void BP_OnMoveOrder(FVector Destination);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sandbox|Visuals")
    TObjectPtr<USceneComponent> SceneRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sandbox|Visuals")
    TObjectPtr<UStaticMeshComponent> VisualMesh;

    /** Set a skeletal mesh in a derived Blueprint to hide the proxy cube. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sandbox|Visuals")
    TObjectPtr<USkeletalMeshComponent> ArtMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sandbox|Visuals")
    TObjectPtr<UTextRenderComponent> Label;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sandbox|Stats")
    ESandboxUnitType UnitType = ESandboxUnitType::Marine;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sandbox|Stats")
    float Health = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sandbox|Stats")
    float MaxHealth = 0.0f;

private:
    int32 UnitId = INDEX_NONE;
    bool bSelected = false;
    bool bDead = false;
    bool bHasMockMoveTarget = false;
    bool bExplicitAttackOrder = false;
    FVector MockMoveTarget = FVector::ZeroVector;
    TWeakObjectPtr<ASandboxUnit> CurrentTarget;

    float MovementSpeed = 0.0f;
    float AttackRange = 0.0f;
    float SightRange = 0.0f;
    float Damage = 0.0f;
    float AttackInterval = 1.0f;
    float CooldownRemaining = 0.0f;
    float SearchRemaining = 0.0f;
    float HitFlashRemaining = 0.0f;

    void FindNearestEnemy();
    void MoveTowards(const FVector& Destination, float DeltaSeconds);
    void Attack(ASandboxUnit* Target);
    void RefreshLabel();
    void Die();
};
