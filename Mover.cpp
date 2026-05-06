#include "Mover.h"

UMover::UMover()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMover::BeginPlay()
{
	Super::BeginPlay();
	if (bMoveRootComponent)
	{
		MoveComponent = GetOwner()->GetRootComponent();
	}
	else
	{
		MoveComponent = Cast<USceneComponent>(ComponentToMove.GetComponent(GetOwner()));
	}

	if (!MoveComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Mover: ComponentToMove is NULL. Nothing will move."));
		return;
	}

	StartLocation = MoveComponent->GetRelativeLocation();
	StartRotation = MoveComponent->GetRelativeRotation();

	FinalLocation = StartLocation;
	FinalRotation = StartRotation;
}

void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!MoveComponent)return;

    FVector CurrentLocation = MoveComponent->GetRelativeLocation();
	if (!CurrentLocation.Equals(FinalLocation, 1.0f))
    {
		MoveComponent->SetRelativeLocation(
			FMath::VInterpTo(CurrentLocation, FinalLocation, DeltaTime, MoveSpeed));
		if (bMoveOnce && CurrentLocation.Equals(FinalLocation, 1.0f))
		{
			SetComponentTickEnabled(false);
			return;
		}
    }
	else
	{
		if (bMoveOnce && CurrentLocation.Equals(FinalLocation, 1.0f) && bShouldMove)
		{
			UE_LOG(LogTemp, Warning, TEXT("Will Not move again"));
			SetComponentTickEnabled(false);
			return;
		}
	}

    FRotator CurrentRotation = MoveComponent->GetRelativeRotation();
	if (!CurrentRotation.Equals(FinalRotation, 1.0f))
    {
		MoveComponent->SetRelativeRotation(
			FMath::RInterpTo(CurrentRotation, FinalRotation, DeltaTime, RotateSpeed));
    }
	else
	{
		if (bMoveOnce && CurrentRotation.Equals(FinalRotation, 1.0f) && bShouldRotate)
		{
			UE_LOG(LogTemp, Warning, TEXT("Will Not move again"));
			SetComponentTickEnabled(false);
			return;
		}
	}
}

void UMover::SetShouldMove(bool bNewShouldMove)
{
	bShouldMove = bNewShouldMove;
    FinalLocation = bShouldMove ? (StartLocation + MoveThreshold) : StartLocation;
}

void UMover::SetShouldRotate(bool bNewShouldRotate)
{
	bShouldRotate = bNewShouldRotate;
    FinalRotation = bShouldRotate ? (StartRotation + RotateThreshold) : StartRotation;
}

bool UMover::GetShouldMove() const { return bShouldMove; }
bool UMover::GetShouldRotate() const { return bShouldRotate; }