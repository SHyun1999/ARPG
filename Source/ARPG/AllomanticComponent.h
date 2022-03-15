// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AllomanticComponent.generated.h"

class AStaticMeshActor;
class UMetalComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_API UAllomanticComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAllomanticComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//traces a line from the player's perspective, returns true if the line traced connects with a moveable object.
	bool TraceAllomanticLines(FHitResult& Hit);
	//sets which metal is being burned.
	bool BurnMetal(int Direction);

	bool SteelIron(int Direction);
	//increases metal burn rate, multiplies strength attribute.
	void BurnPewter();
	//HIGHLIGHTS which items allomancy can interact with
	void BurnTin();

private:
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


	bool EnhancedSteelIron(int Direction);
	void TraceTinLines();
	bool bIsBurningTin = false;

	class AARPGCharacter* OwnerPawn;

	UPROPERTY(EditAnywhere, Category = "Allomancy")
		float TraceDistance = 3000.f;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
		float ImpulseForce = 2.f;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
		float PewterStrMultiplier = 1.8f;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
		float PewterDrainingMultiplier = .5f;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
		float TinDrainingMultiplier = .3f;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	UStaticMeshComponent* LastMetalComponent;

	AStaticMeshActor* LastActor;
};
