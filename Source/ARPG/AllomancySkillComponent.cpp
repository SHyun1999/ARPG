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

	// ...
	
}

// Called every frame
void UAllomancySkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


bool UAllomancySkillComponent::CastAction(int Direction)
{
	return true;
}

FVector UAllomancySkillComponent::GetForceToApplyVector(AActor* Actor)
{
	FVector Start = Actor->GetActorLocation();
	FVector End = this->OwnerPawn->GetActorLocation();

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

void UAllomancySkillComponent::SetActionCost(float a)
{
	ActionCost = a;
}

float UAllomancySkillComponent::GetActionCost()
{
	return ActionCost;
}

void UAllomancySkillComponent::SetToggleable(bool Toggleable)
{
	bIsToggleable = Toggleable;
}

bool UAllomancySkillComponent::GetToggleable()
{
	return bIsToggleable;
}