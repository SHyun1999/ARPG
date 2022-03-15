// Fill out your copyright notice in the Description page of Project Settings.


#include "DuraluminAluminumComponent.h"
#include "ARPGCharacter.h"
#include "MetalReserveComponent.h"

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