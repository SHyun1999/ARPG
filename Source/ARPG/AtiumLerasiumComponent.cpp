// Fill out your copyright notice in the Description page of Project Settings.


#include "AtiumLerasiumComponent.h"
#include "ARPGCharacter.h"
#include "TimerManager.h"
#include "Kismet/GamePlayStatics.h"
#include "MetalReserveComponent.h"

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
		bIsBurningAtium = !bIsBurningAtium;
		float TimeDilation;
		float CustomTimeDilation;
		if (Direction > 0)
		{
			TimeDilation = AtiumTimeDilation;
			CustomTimeDilation = AtiumCustomTime;
		}
		else
		{
			TimeDilation = LerasiumTimeDilation;
			CustomTimeDilation = 1.f;
		}
		if (bIsBurningAtium) 
		{
			BurnAtiumLerasium(TimeDilation, CustomTimeDilation);
		}
		return true;

	}
	return false;
}

void UAtiumLerasiumComponent::BurnAtiumLerasium(float TimeDilation, float CustomTimeDilation)
{
	bIsBurningAtium = true;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeDilation);
	OwnerPawn->CustomTimeDilation = CustomTimeDilation;
}