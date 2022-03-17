// Fill out your copyright notice in the Description page of Project Settings.


#include "PewterTinComponent.h"
#include "ARPGCharacter.h"
#include "DrawDebugHelpers.h"
#include "MetalComponent.h"
#include "Engine/StaticMeshActor.h"


// Sets default values for this component's properties
UPewterTinComponent::UPewterTinComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bIsToggleable = true;
}

bool UPewterTinComponent::CastAction(int Direction, float DrainingMultiplier)
{
	Super::CastAction(Direction, DrainingMultiplier);
	return(BurnMetal(Direction));
}

// Called every frame
void UPewterTinComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsBurningTin)
	{
		TraceTinLines();
	}
}

bool UPewterTinComponent::BurnMetal(int Direction)
{
	if (!HasOwner()) return false;
	if (OwnerPawn->bIsBurningMetal) 
	{
		if (Direction > 0)
		{
			return BurnPewter();
		}
		else
		{
			return BurnTin();
		}

	}
	return false;
}

bool UPewterTinComponent::BurnPewter()
{
	OwnerPawn->setSTR(OwnerPawn->STR * PewterStrMultiplier);
	return true;
}

bool UPewterTinComponent::BurnTin()
{
	bIsBurningTin = true;
	return bIsBurningTin;
}

void UPewterTinComponent::TraceTinLines() //maybe refactor to make more efficient
{
	for (TObjectIterator<AStaticMeshActor> ObjectItr; ObjectItr; ++ObjectItr)
	{
		AStaticMeshActor* Actor = Cast<AStaticMeshActor>(*ObjectItr);
		UMetalComponent* MetComp = Actor->FindComponentByClass<UMetalComponent>();
		if (MetComp)
		{
			if (!MetComp->bIsAlluminum)
			{
				FVector Start = Actor->GetActorLocation();
				FVector End = OwnerPawn->GetActorLocation();
				DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, .1f);
			}
		}
	}
}