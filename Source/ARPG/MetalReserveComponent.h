// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MetalReserveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_API UMetalReserveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMetalReserveComponent();

	// checks if enough to cast allomantic ability.
	bool CanCastAllomanticAction(int ActionCost);

	void ReduceMetalReserve(float QuantToRemove);

	//resets draining ratio value. TODO: Set variable
	void ResetDrainingRatio();

	//returns percentage of metal reserves.
	UFUNCTION(BlueprintPure)
	float GetMetalReservePercent() const;

	void DrainMetalReserves();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	class AARPGCharacter* OwnerPawn;
	float MaxMetalReserve = 100.f;

		
};
