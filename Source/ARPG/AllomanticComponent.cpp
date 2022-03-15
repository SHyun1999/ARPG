// Fill out your copyright notice in the Description page of Project Settings.


#include "AllomanticComponent.h"
#include "ARPGCharacter.h"
#include "DrawDebugHelpers.h"
#include "MetalComponent.h"
#include "Engine/StaticMeshActor.h"


// Sets default values for this component's properties
UAllomanticComponent::UAllomanticComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OwnerPawn = Cast<AARPGCharacter>(GetOwner());
	// ...
}


// Called when the game starts
void UAllomanticComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAllomanticComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsBurningTin)
	{
		TraceTinLines();
	}
}

bool UAllomanticComponent::BurnMetal(int Direction)
{
	if (!HasOwner()) return false;
	if (Direction >0)
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

void UAllomanticComponent::BurnPewter()
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

void UAllomanticComponent::BurnTin()
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

void UAllomanticComponent::TraceTinLines() //maybe refactor to make more efficient
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

bool UAllomanticComponent::TraceAllomanticLines(FHitResult& Hit)
{

	if (!HasOwner()) return false;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return false;

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

FVector UAllomanticComponent::GetEndVector(AController* OwnerController)
{
	FVector Loc;
	FRotator Rot;
	OwnerController->GetPlayerViewPoint(Loc, Rot);//these are out params

	return Loc + Rot.Vector() * TraceDistance;
}

bool UAllomanticComponent::SteelIron(int Direction)
{
	if (OwnerPawn->bDuraluminFlare)
	{
		return EnhancedSteelIron(Direction);
	}
	FHitResult Hit;
	if (TraceAllomanticLines(Hit))
	{
		UStaticMeshComponent* MeshComponent = GetMeshComp(Hit);
		UMetalComponent* MetalComponent = GetMetalComp(Hit);
		if (MetalComponent && MeshComponent)  //Check if is metal, and exists, and is movable.
		{
			if (MetalComponent->bIsAlluminum) return false ; //allomancy doesn't affect alluminum!
			MeshComponent->AddImpulse(GetForceToApplyVector(Hit.GetActor()) * (OwnerPawn->GetMesh()->GetMass()/2) * Direction);
			OwnerPawn->ACharacter::LaunchCharacter(GetForceToApplyVector(Hit.GetActor()) * (MeshComponent->GetMass()/6) * Direction * -1, false, true);
			return true;
		}
		return false;
	}
	return false;
}

bool UAllomanticComponent::EnhancedSteelIron(int Direction)
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

//////////////////////////////////////Getters
/////////////////////////////////////////////////////////////////////////
bool UAllomanticComponent::HasOwner()
{
	return OwnerPawn != nullptr;
}

UMetalComponent* UAllomanticComponent::GetMetalComp(FHitResult Hit)
{
	return Cast<UMetalComponent>(Hit.GetActor()->FindComponentByClass<UMetalComponent>());
}

UStaticMeshComponent* UAllomanticComponent::GetMeshComp(FHitResult Hit)
{
	return Cast<UStaticMeshComponent>(Hit.GetActor()->GetRootComponent());
}

FVector UAllomanticComponent::GetForceToApplyVector(AActor* Actor)
{
	FVector Start = Actor->GetActorLocation();
	FVector End = this->OwnerPawn->GetActorLocation();
	
	FVector ForceToApply = Start - End;
	return ForceToApply + ImpulseForce;
}