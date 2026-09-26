#include "AdventureHUD.h"
#include "AdventurePlayerController.h"
#include "InteractableActor.h"
#include "Engine/Canvas.h"

void AAdventureHUD::DrawHUD()
{
	Super::DrawHUD();

	const AAdventurePlayerController* PC = Cast<AAdventurePlayerController>(GetOwningPlayerController());
	if (!PC || !Canvas)
	{
		return;
	}

	if (const AInteractableActor* Hovered = PC->GetHoveredActor())
	{
		float MouseX = 0.f;
		float MouseY = 0.f;
		if (PC->GetMousePosition(MouseX, MouseY))
		{
			DrawText(Hovered->DisplayName.ToString(), FLinearColor::White, MouseX + 20.f, MouseY + 20.f, nullptr, 1.3f);
		}
	}

	const FText Message = PC->GetCurrentMessage();
	if (!Message.IsEmpty())
	{
		DrawText(Message.ToString(), FLinearColor::Yellow, 40.f, Canvas->ClipY - 90.f, nullptr, 1.6f);
	}

	TArray<FString> Names;
	for (const FText& Name : PC->GetInventoryNames())
	{
		Names.Add(Name.ToString());
	}
	const FString InventoryLine = TEXT("Inventar: ") + (Names.Num() > 0 ? FString::Join(Names, TEXT(", ")) : TEXT("leer"));
	DrawText(InventoryLine, FLinearColor::White, 40.f, 30.f, nullptr, 1.2f);
}
