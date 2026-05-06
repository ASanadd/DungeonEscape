// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"
#include "Mover.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEONESCAPE_API UMover : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	bool bShouldRotate = false;
	UPROPERTY(VisibleAnywhere)
	bool bShouldMove = false;
	UPROPERTY(EditAnywhere)
	bool bMoveOnce = false;
	UPROPERTY(EditAnywhere, Category = "Mover")
	bool bMoveRootComponent = false;

public:
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool GetShouldMove (void) const;
	void SetShouldMove(bool NewShouldMove);
	bool GetShouldRotate(void) const;
	void SetShouldRotate(bool NewShouldRotate);

	UPROPERTY(EditInstanceOnly, Category = "Mover")
	FComponentReference ComponentToMove;

	UPROPERTY(VisibleAnywhere, Category = "Mover")
	USceneComponent* MoveComponent = nullptr;

	UPROPERTY(EditAnywhere)
	FVector MoveThreshold;
	FVector StartLocation;
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 4.0f;

	UPROPERTY(EditAnywhere)
	FRotator RotateThreshold;
	FRotator StartRotation;
	UPROPERTY(EditAnywhere)
	float RotateSpeed = 4.0f;

	FVector FinalLocation;
	FRotator FinalRotation;

};
