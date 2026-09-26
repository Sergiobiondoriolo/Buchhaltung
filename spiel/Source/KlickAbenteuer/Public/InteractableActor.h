#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

class AAdventurePlayerController;
class UStaticMeshComponent;

/**
 * Ein anklickbares Objekt ("Hotspot") in der Welt.
 * - Nur Beschreibung: Spieler schaut es an.
 * - bCanPickUp: landet im Inventar.
 * - RequiredItemId: braucht einen Gegenstand aus dem Inventar (Raetsel).
 */
UCLASS(Blueprintable)
class KLICKABENTEUER_API AInteractableActor : public AActor
{
	GENERATED_BODY()

public:
	AInteractableActor();

	/** Wird aufgerufen, sobald die Figur nah genug ist. */
	void Interact(AAdventurePlayerController* PlayerController);

	/** Name, der beim Drueberfahren mit der Maus erscheint. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abenteuer")
	FText DisplayName;

	/** Text beim Anschauen. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abenteuer", meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abenteuer")
	bool bCanPickUp = false;

	/** Kennung im Inventar, z. B. "Schluessel". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abenteuer", meta = (EditCondition = "bCanPickUp"))
	FName ItemId;

	/** Wenn gesetzt, muss dieser Gegenstand im Inventar sein (z. B. Tuer braucht "Schluessel"). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abenteuer|Raetsel")
	FName RequiredItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abenteuer|Raetsel", meta = (MultiLine = true))
	FText SolvedText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abenteuer|Raetsel", meta = (MultiLine = true))
	FText MissingItemText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abenteuer|Raetsel")
	bool bConsumeRequiredItem = true;

	UPROPERTY(BlueprintReadOnly, Category = "Abenteuer|Raetsel")
	bool bSolved = false;

	/** Wie nah die Figur herankommen muss. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abenteuer")
	float InteractDistance = 180.f;

	/** In Blueprints ueberschreibbar: z. B. Tuer oeffnen, Sound abspielen. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Abenteuer")
	void OnInteracted(AAdventurePlayerController* PlayerController);

	UFUNCTION(BlueprintImplementableEvent, Category = "Abenteuer")
	void OnSolved(AAdventurePlayerController* PlayerController);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abenteuer")
	TObjectPtr<UStaticMeshComponent> Mesh;
};
