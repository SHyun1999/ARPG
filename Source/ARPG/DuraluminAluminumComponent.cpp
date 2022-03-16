// Fill out your copyright notice in the Description page of Project Settings.


#include "DuraluminAluminumComponent.h"
#include "ARPGCharacter.h"
#include "MetalReserveComponent.h"

// Sets default values for this component's properties
UDuraluminAluminumComponent::UDuraluminAluminumComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bIsToggleable = false;
}

void UDuraluminAluminumComponent::SetDuraluminEnhancement()
{
	UE_LOG(LogTemp, Warning,TEXT("%s"), *OwnerPawn->GetName())
	if (!OwnerPawn) return;
	OwnerPawn->DuraluminEnhancementMultiplier = OwnerPawn->CurrentMetalReserve * .03;
}

void UDuraluminAluminumComponent::DrainMetalReserves()
{
	OwnerPawn->MetalReserveComponent->DrainMetalReserves();
}