// Fill out your copyright notice in the Description page of Project Settings.


#include "PewterTinComponent.h"
#include "ARPGCharacter.h"
#include "DrawDebugHelpers.h"
#include "MetalComponent.h"
#include "Engine/StaticMeshActor.h"

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
	if (Direction > 0)
	{
		BurnPewter();
		return true;
	}
	else
	{
		BurnTin();
		return true;
	}
	return false;
}

void UPewterTinComponent::BurnPewter()
{

	if (OwnerPawn->bIsBurningMetal)
	{
		OwnerPawn->DrainingRatio = OwnerPawn->DrainingRatio + PewterDrainingMultiplier;
		OwnerPawn->setSTR(OwnerPawn->STR * PewterStrMultiplier);
	}
	else
	{
		OwnerPawn->TryResetDrainingRatio();
		OwnerPawn->ResetStrValue();
		bIsBurningTin = false;
	}
}

void UPewterTinComponent::BurnTin()
{
	if (OwnerPawn->bIsBurningMetal)
	{
		OwnerPawn->DrainingRatio = OwnerPawn->DrainingRatio + TinDrainingMultiplier;
		bIsBurningTin = true;
	}
	else
	{
		OwnerPawn->TryResetDrainingRatio();
		bIsBurningTin = false;
		OwnerPawn->ResetStrValue();
	}
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
				DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 0);
			}
		}
	}
}