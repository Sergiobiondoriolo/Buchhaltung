#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AdventureGameMode.generated.h"

/** Verbindet Spielfigur, Steuerung und HUD des Klick-Adventures. */
UCLASS()
class KLICKABENTEUER_API AAdventureGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAdventureGameMode();
};
