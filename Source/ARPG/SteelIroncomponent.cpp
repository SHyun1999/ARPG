// Fill out your copyright notice in the Description page of Project Settings.


#include "SteelIronComponent.h"
#include "ARPGCharacter.h"
#include "DrawDebugHelpers.h"
#include "MetalComponent.h"
#include "Engine/StaticMeshActor.h"


// Sets default values for this component's properties
USteelIronComponent::USteelIronComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}

bool USteelIronComponent::CastAction(int Direction)
{
	return(SteelIron(Direction));
}

bool USteelIronComponent::SteelIron(int Direction)
{
	if (!OwnerPawn)  return false; 
	if (OwnerPawn->bDuraluminFlare)
	{
		return EnhancedSteelIron(Direction);
		return false;
	}
	FHitResult Hit;
	if (TraceAllomanticLines(Hit))
	{
		UStaticMeshComponent* MeshComponent = GetMeshComp(Hit);
		UMetalComponent* MetalComponent = GetMetalComp(Hit);
		if (MetalComponent && MeshComponent)  //Check if is metal, and exists, and is movable.
		{
			if (MetalComponent->bIsAlluminum) return false; //allomancy doesn't affect alluminum!
			MeshComponent->AddImpulse(GetForceToApplyVector(Hit.GetActor()) * (OwnerPawn->GetMesh()->GetMass() / 2) * Direction);
			OwnerPawn->ACharacter::LaunchCharacter(GetForceToApplyVector(Hit.GetActor()) * (MeshComponent->GetMass() / 6) * Direction * -1, false, true);
			return true;
		}
		return false;
	}
	return false;
}

bool USteelIronComponent::TraceAllomanticLines(FHitResult& Hit)
{

	if (!HasOwner()) return false;
	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) return false;

	const FVector Start = OwnerPawn->GetActorLocation();
	FVector End = GetEndVector(OwnerController);

	FCollisionQueryParams TraceParams;

	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, .5f);
	return GetWorld()->LineTraceSingleByChannel(Hit,
		Start,
		End,
		ECollisionChannel::ECC_Visibility, // check defaultengine.ini file to get bullet collision channel
		TraceParams);
}

bool USteelIronComponent::EnhancedSteelIron(int Direction)
{
	for (TObjectIterator<AStaticMeshActor> ObjectItr; ObjectItr; ++ObjectItr)
	{
		AStaticMeshActor* Actor = Cast<AStaticMeshActor>(*ObjectItr);
		UMetalComponent* MetComp = Actor->FindComponentByClass<UMetalComponent>();
		if (MetComp)
		{
			if (!MetComp->bIsAlluminum)
			{
				UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(Actor->GetRootComponent());
				MeshComponent->AddImpulse(GetForceToApplyVector(Actor) * OwnerPawn->GetMesh()->GetMass() * OwnerPawn->DuraluminEnhancementMultiplier * Direction);
				LastActor = Actor;
				LastMetalComponent = MeshComponent;
			}
		}
	}
	OwnerPawn->ACharacter::LaunchCharacter(GetForceToApplyVector(LastActor) * (LastMetalComponent->GetMass() / 8) * Direction * -1, false, true);
	return true;
}