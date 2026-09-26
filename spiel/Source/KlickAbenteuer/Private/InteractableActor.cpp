#include "InteractableActor.h"
#include "AdventurePlayerController.h"
#include "Components/StaticMeshComponent.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName(TEXT("BlockAll"));

	DisplayName = NSLOCTEXT("KlickAbenteuer", "DefaultName", "Gegenstand");
	Description = NSLOCTEXT("KlickAbenteuer", "DefaultDesc", "Nichts Besonderes.");
}

void AInteractableActor::Interact(AAdventurePlayerController* PlayerController)
{
	if (!PlayerController)
	{
		return;
	}

	if (!RequiredItemId.IsNone() && !bSolved)
	{
		if (PlayerController->HasItem(RequiredItemId))
		{
			if (bConsumeRequiredItem)
			{
				PlayerController->RemoveItem(RequiredItemId);
			}
			bSolved = true;
			PlayerController->ShowMessage(SolvedText);
			OnSolved(PlayerController);
		}
		else
		{
			PlayerController->ShowMessage(MissingItemText.IsEmpty() ? Description : MissingItemText);
		}
		return;
	}

	if (bCanPickUp)
	{
		PlayerController->AddItem(ItemId.IsNone() ? GetFName() : ItemId, DisplayName);
		PlayerController->ShowMessage(FText::Format(
			NSLOCTEXT("KlickAbenteuer", "PickedUp", "{0} eingesteckt."), DisplayName));
		OnInteracted(PlayerController);
		Destroy();
		return;
	}

	PlayerController->ShowMessage(Description);
	OnInteracted(PlayerController);
}
