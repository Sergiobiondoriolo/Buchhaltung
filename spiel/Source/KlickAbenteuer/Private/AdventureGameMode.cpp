#include "AdventureGameMode.h"
#include "AdventureCharacter.h"
#include "AdventurePlayerController.h"
#include "AdventureHUD.h"

AAdventureGameMode::AAdventureGameMode()
{
	DefaultPawnClass = AAdventureCharacter::StaticClass();
	PlayerControllerClass = AAdventurePlayerController::StaticClass();
	HUDClass = AAdventureHUD::StaticClass();
}
