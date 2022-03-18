// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AllomancySkillComponent.generated.h"

class AStaticMeshActor;
class UMetalComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_API UAllomancySkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAllomancySkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	//base cast action
	virtual bool CastAction(int Direction, float DrainingMultiplier);

	class AARPGCharacter* OwnerPawn;

	//checks if allomantic component has owner.
	bool HasOwner();
	//returns metal component of the hit object.
	UMetalComponent* GetMetalComp(FHitResult Hit);
	//return static mesh component of the hit object.
	UStaticMeshComponent* GetMeshComp(FHitResult Hit);
	// returns forward vector multiplied by ImpulseForce
	FVector GetForceToApplyVector(AActor* Actor);
	//returns player location + rotation + trace distance.
	FVector GetEndVector(AController* OwnerController);

		void ResetTime();
	UPROPERTY(EditAnywhere, Category = "Allomancy")
		float TraceDistance = 3000.f;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
		float ImpulseForce = 2.f;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
		float PewterStrMultiplier = 1.8f;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
		UStaticMeshComponent* LastMetalComponent;

	AStaticMeshActor* LastActor;

	//see if allomantic skill is toggleable
	bool bIsToggleable;
	//check if burning tin
	bool bIsBurningTin = false;
	//check if burning atium
	bool bIsBurningAtium = false;
	//check if burning copper
	bool bIsBurningCopper= false;
	//check if burning bronze
	bool bIsBurningBronze = false;

};
