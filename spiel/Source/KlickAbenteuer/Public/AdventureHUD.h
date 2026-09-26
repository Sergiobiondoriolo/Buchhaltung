#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AdventureHUD.generated.h"

/** Einfache Textanzeige: Objektname unter der Maus, Meldungen, Inventar. */
UCLASS()
class KLICKABENTEUER_API AAdventureHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
};
