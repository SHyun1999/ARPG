// Fill out your copyright notice in the Description page of Project Settings.


#include "MetalReserveComponent.h"
#include "ARPGCharacter.h"

// Sets default values for this component's properties
UMetalReserveComponent::UMetalReserveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OwnerPawn = Cast<AARPGCharacter>(GetOwner());
}

// Called every frame
void UMetalReserveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Called when the game starts
void UMetalReserveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UMetalReserveComponent::ResetDrainingRatio()
{
	OwnerPawn->DrainingRatio = 0.1;
}

float UMetalReserveComponent::GetMetalReservePercent() const
{
	return OwnerPawn->CurrentMetalReserve / MaxMetalReserve;
}

void UMetalReserveComponent::ReduceMetalReserve(float QuantToRemove)
{
	QuantToRemove = FMath::Min(OwnerPawn->CurrentMetalReserve, QuantToRemove);
	OwnerPawn->CurrentMetalReserve -= QuantToRemove;
}

bool UMetalReserveComponent::CanCastAllomanticAction(int ActionCost)
{
	return ActionCost < OwnerPawn->CurrentMetalReserve;
}

void UMetalReserveComponent::DrainMetalReserves()
{
	OwnerPawn->CurrentMetalReserve = 0;
}