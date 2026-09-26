#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AdventureCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * Spielfigur mit schraeger Kamera von oben.
 * Tipp: Im Editor eine Blueprint-Unterklasse anlegen und dort ein Mesh
 * (z. B. Manny oder einen MetaHuman) zuweisen.
 */
UCLASS()
class KLICKABENTEUER_API AAdventureCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAdventureCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kamera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kamera")
	TObjectPtr<UCameraComponent> Camera;
};
