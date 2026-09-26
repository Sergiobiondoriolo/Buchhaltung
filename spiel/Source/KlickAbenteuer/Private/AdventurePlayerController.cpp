#include "AdventurePlayerController.h"
#include "InteractableActor.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Navigation/PathFollowingComponent.h"

AAdventurePlayerController::AAdventurePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AAdventurePlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}

void AAdventurePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateHover();

	if (WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		HandleClick();
	}

	UpdatePendingInteraction();
}

void AAdventurePlayerController::UpdateHover()
{
	FHitResult Hit;
	HoveredActor = GetHitResultUnderCursor(ECC_Visibility, false, Hit)
		? Cast<AInteractableActor>(Hit.GetActor())
		: nullptr;
	CurrentMouseCursor = HoveredActor ? EMouseCursor::Hand : EMouseCursor::Default;
}

void AAdventurePlayerController::HandleClick()
{
	FHitResult Hit;
	if (!GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		return;
	}

	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn)
	{
		return;
	}

	if (AInteractableActor* Target = Cast<AInteractableActor>(Hit.GetActor()))
	{
		PendingTarget = Target;

		// Zu einem Punkt vor dem Objekt laufen, nicht in das Objekt hinein.
		const FVector TargetLocation = Target->GetActorLocation();
		FVector ToPawn = ControlledPawn->GetActorLocation() - TargetLocation;
		ToPawn.Z = 0.f;
		const FVector Goal = TargetLocation + ToPawn.GetSafeNormal() * Target->InteractDistance * 0.7f;
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Goal);
	}
	else
	{
		PendingTarget = nullptr;
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.Location);
	}
}

void AAdventurePlayerController::UpdatePendingInteraction()
{
	APawn* ControlledPawn = GetPawn();
	if (!PendingTarget || !ControlledPawn)
	{
		return;
	}

	const float Distance = FVector::Dist2D(ControlledPawn->GetActorLocation(), PendingTarget->GetActorLocation());
	if (Distance <= PendingTarget->InteractDistance)
	{
		StopMovement();
		AInteractableActor* Target = PendingTarget;
		PendingTarget = nullptr;
		Target->Interact(this);
		return;
	}

	// Figur steht, ist aber nicht angekommen: kein Weg dorthin.
	const UPathFollowingComponent* PathFollowing = FindComponentByClass<UPathFollowingComponent>();
	if (PathFollowing && PathFollowing->GetStatus() == EPathFollowingStatus::Idle)
	{
		PendingTarget = nullptr;
		ShowMessage(NSLOCTEXT("KlickAbenteuer", "NoPath", "Da komme ich nicht hin."));
	}
}

void AAdventurePlayerController::ShowMessage(const FText& Text, float Duration)
{
	CurrentMessage = Text;
	MessageEndTime = GetWorld()->GetTimeSeconds() + Duration;
}

FText AAdventurePlayerController::GetCurrentMessage() const
{
	return GetWorld()->GetTimeSeconds() < MessageEndTime ? CurrentMessage : FText::GetEmpty();
}

bool AAdventurePlayerController::HasItem(FName ItemId) const
{
	return Inventory.Contains(ItemId);
}

void AAdventurePlayerController::AddItem(FName ItemId, const FText& DisplayName)
{
	Inventory.Add(ItemId, DisplayName);
}

void AAdventurePlayerController::RemoveItem(FName ItemId)
{
	Inventory.Remove(ItemId);
}

TArray<FText> AAdventurePlayerController::GetInventoryNames() const
{
	TArray<FText> Names;
	Inventory.GenerateValueArray(Names);
	return Names;
}
