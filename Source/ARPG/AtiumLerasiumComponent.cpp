// Fill out your copyright notice in the Description page of Project Settings.


#include "AtiumLerasiumComponent.h"
#include "ARPGCharacter.h"

// Sets default values for this component's properties
UAtiumLerasiumComponent::UAtiumLerasiumComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bIsToggleable = true;
}

bool UAtiumLerasiumComponent::CastAction(int Direction, float DrainingMultiplier)
{
	Super::CastAction(Direction, DrainingMultiplier);
	return BurnMetal(Direction);

}

bool UAtiumLerasiumComponent::BurnMetal(int Direction)
{
	if (!HasOwner()) return false;
	if (OwnerPawn->bIsBurningMetal)
	{
		if (Direction > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("CHAD ATIUM"));
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("VIRGIN LERASIUM"));
			return false;
		}

	}
	return false;
}