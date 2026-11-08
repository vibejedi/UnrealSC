#include "RTSCameraPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"

ARTSCameraPawn::ARTSCameraPawn()
{
    PrimaryActorTick.bCanEverTick = true;
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraPivot"));
    RootComponent = Pivot;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(Pivot);
    SpringArm->TargetArmLength = 1800.0f;
    SpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
    SpringArm->bDoCollisionTest = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ARTSCameraPawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    const FVector Direction(MoveForwardInput, MoveRightInput, 0.0f);
    const FVector Movement = Direction.GetClampedToMaxSize(1.0f) * PanSpeed * DeltaSeconds;
    AddActorWorldOffset(Movement, true);
}

void ARTSCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("RTSForward"), this, &ARTSCameraPawn::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("RTSRight"), this, &ARTSCameraPawn::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("RTSZoom"), this, &ARTSCameraPawn::Zoom);
}

void ARTSCameraPawn::MoveForward(float Value) { MoveForwardInput = Value; }
void ARTSCameraPawn::MoveRight(float Value) { MoveRightInput = Value; }

void ARTSCameraPawn::Zoom(float Value)
{
    if (SpringArm && !FMath::IsNearlyZero(Value))
    {
        SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength - Value * ZoomStep, MinZoom, MaxZoom);
    }
}
