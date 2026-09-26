#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AdventurePlayerController.generated.h"

class AInteractableActor;

/** Point-and-Click-Steuerung: Linksklick = hinlaufen bzw. Objekt benutzen. */
UCLASS()
class KLICKABENTEUER_API AAdventurePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAdventurePlayerController();

	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Abenteuer")
	void ShowMessage(const FText& Text, float Duration = 4.f);

	UFUNCTION(BlueprintCallable, Category = "Abenteuer|Inventar")
	bool HasItem(FName ItemId) const;

	UFUNCTION(BlueprintCallable, Category = "Abenteuer|Inventar")
	void AddItem(FName ItemId, const FText& DisplayName);

	UFUNCTION(BlueprintCallable, Category = "Abenteuer|Inventar")
	void RemoveItem(FName ItemId);

	TArray<FText> GetInventoryNames() const;
	FText GetCurrentMessage() const;
	AInteractableActor* GetHoveredActor() const { return HoveredActor; }

protected:
	virtual void BeginPlay() override;

private:
	void HandleClick();
	void UpdateHover();
	void UpdatePendingInteraction();

	UPROPERTY()
	TObjectPtr<AInteractableActor> HoveredActor;

	UPROPERTY()
	TObjectPtr<AInteractableActor> PendingTarget;

	UPROPERTY()
	TMap<FName, FText> Inventory;

	FText CurrentMessage;
	double MessageEndTime = 0.0;
};
