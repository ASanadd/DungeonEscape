// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MoverActor)
	{
		Mover = MoverActor->FindComponentByClass<UMover>();
		if (Mover)
		{
			UE_LOG(LogTemp, Display, TEXT("Successfully found a mover component!"));				
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Couldn't find mover component for that actor"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Couldn't find actor pointer"));
	}

	if (bIsPressurePlateMove || bIsPressurePlateRotate)
	{
		UE_LOG(LogTemp, Display, TEXT("Set up pressure plate successful"));
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
		OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);

		UpdateOverlaps();
		UpdateTriggerState();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Set up pressure plate failed"));
	}

}	

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UpdateTriggerState();
}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UpdateTriggerState();
}

void UTriggerComponent::UpdateTriggerState()
{
	if (!Mover) return;

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	int32 ValidActivators = 0;
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("PressurePlateActivator"))
		{
			ValidActivators++;
		}
	}

	bool bShouldTrigger = (ValidActivators > 0);

	// Only call Trigger when state actually changes
	if (bShouldTrigger != bIsTriggered)
	{
		Trigger(bShouldTrigger);
	}
}

void UTriggerComponent::Trigger(bool bNewTriggerValue)
{
	UE_LOG(LogTemp, Display, TEXT("Triggering mover component! Value: %s"),
		bNewTriggerValue ? TEXT("TRUE") : TEXT("FALSE"));
	bIsTriggered = bNewTriggerValue;
	if (bIsPressurePlateMove)
	{
		Mover->SetShouldMove(bIsTriggered);
	}
	else if (bIsPressurePlateRotate)
	{
		Mover->SetShouldRotate(bIsTriggered);
	}
}