#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSCameraPawn.generated.h"

class USceneComponent;
class USpringArmComponent;
class UCameraComponent;

/** Presentation-only RTS camera. It never controls simulation state. */
UCLASS()
class UNREALSC_API ARTSCameraPawn : public APawn
{
    GENERATED_BODY()
public:
    ARTSCameraPawn();
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="RTS Camera")
    TObjectPtr<USceneComponent> Pivot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="RTS Camera")
    TObjectPtr<USpringArmComponent> SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="RTS Camera")
    TObjectPtr<UCameraComponent> Camera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS Camera", meta=(ClampMin="0.0"))
    float PanSpeed = 1800.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS Camera", meta=(ClampMin="100.0"))
    float MinZoom = 700.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS Camera", meta=(ClampMin="100.0"))
    float MaxZoom = 3200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS Camera", meta=(ClampMin="0.0"))
    float ZoomStep = 250.0f;

private:
    float MoveForwardInput = 0.0f;
    float MoveRightInput = 0.0f;
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Zoom(float Value);
};
