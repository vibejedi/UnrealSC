#include "RTSGameMode.h"
#include "RTSCameraPawn.h"
#include "RTSPlayerController.h"

ARTSGameMode::ARTSGameMode()
{
    DefaultPawnClass = ARTSCameraPawn::StaticClass();
    PlayerControllerClass = ARTSPlayerController::StaticClass();
}
