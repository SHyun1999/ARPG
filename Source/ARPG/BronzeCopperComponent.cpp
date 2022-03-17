// Fill out your copyright notice in the Description page of Project Settings.


#include "BronzeCopperComponent.h"
#include "ARPGCharacter.h"
#include "Kismet\KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

UBronzeCopperComponent::UBronzeCopperComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bIsToggleable = true;
}

// Called every frame
void UBronzeCopperComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsBurningCopper)
	{
		SearchAllomanticPulse();
	}
}

bool UBronzeCopperComponent::CastAction(int Direction, float DrainingMultiplier)
{
	Super::CastAction(Direction, DrainingMultiplier);
	return BurnMetal(Direction);
}


bool UBronzeCopperComponent::BurnMetal(int Direction)
{
	if (!HasOwner()) return false;
	if (OwnerPawn->bIsBurningMetal)
	{
		if (Direction > 0)
		{
			bIsBurningCopper = true;
		}
		else
		{
			OwnerPawn->bIsHiddingPulses = true;
		}

	}
	return true;
}
bool UBronzeCopperComponent::SearchAllomanticPulse()
{
	if (!OwnerPawn) return false;
	
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Init(OwnerPawn, 1);
	TArray<AActor*> OutActors;
	float Radius = 750.0f;
	FVector SphereSpawnLocation = OwnerPawn->GetActorLocation();
	UClass* SeekClass = AARPGCharacter::StaticClass();

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), SphereSpawnLocation, Radius, TraceObjectTypes, SeekClass, IgnoreActors, OutActors);

	for (AActor* OverlappedActor : OutActors) 
	{
		AARPGCharacter* Allomancer = Cast<AARPGCharacter>(OverlappedActor);
		if (Allomancer->bIsBurningMetal && !Allomancer->bIsHiddingPulses)
		{
			DrawDebugSphere(GetWorld(), Allomancer->GetActorLocation(), 30, 12, FColor::Red, false, 0.f);
		}
		
	}
	return true;
}


