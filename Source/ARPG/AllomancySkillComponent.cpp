// Fill out your copyright notice in the Description page of Project Settings.


#include "AllomancySkillComponent.h"
#include "ARPGCharacter.h"
#include "DrawDebugHelpers.h"
#include "MetalComponent.h"
#include "Engine/StaticMeshActor.h"

// Sets default values for this component's properties
UAllomancySkillComponent::UAllomancySkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OwnerPawn = Cast<AARPGCharacter>(GetOwner());
}


// Called when the game starts
void UAllomancySkillComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UAllomancySkillComponent::CastAction(int Direction, float DrainingMultiplier)
{
	if (OwnerPawn->bIsBurningMetal)
	{
		OwnerPawn->DrainingRatio = OwnerPawn->DrainingRatio + DrainingMultiplier;
	}
	else if (!OwnerPawn->bIsBurningMetal)
	{
		OwnerPawn->TryResetDrainingRatio();
		OwnerPawn->ResetStrValue();
		bIsBurningTin = false;
	}
	return true;
}

FVector UAllomancySkillComponent::GetForceToApplyVector(AActor* Actor)
{
	FVector Start = Actor->GetActorLocation();
	FVector End = OwnerPawn->GetActorLocation();

	FVector ForceToApply = Start - End;
	return ForceToApply + ImpulseForce;
}

FVector UAllomancySkillComponent::GetEndVector(AController* OwnerController)
{
	FVector Loc;
	FRotator Rot;
	OwnerController->GetPlayerViewPoint(Loc, Rot);//these are out params

	return Loc + Rot.Vector() * TraceDistance;
}

//////////////////////////////////////Getters
/////////////////////////////////////////////////////////////////////////

UMetalComponent* UAllomancySkillComponent::GetMetalComp(FHitResult Hit)
{
	return Cast<UMetalComponent>(Hit.GetActor()->FindComponentByClass<UMetalComponent>());
}

UStaticMeshComponent* UAllomancySkillComponent::GetMeshComp(FHitResult Hit)
{
	return Cast<UStaticMeshComponent>(Hit.GetActor()->GetRootComponent());
}

bool UAllomancySkillComponent::HasOwner()
{
	return OwnerPawn != nullptr;
}