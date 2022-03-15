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
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual bool CastAction(int Direction);
	
	void SetActionCost(float a);
	float GetActionCost();

	void SetToggleable(bool Toggleable);
	bool GetToggleable();

	class AARPGCharacter* OwnerPawn;
	float ActionCost;
	bool bIsToggleable;

	bool HasOwner();
	UMetalComponent* GetMetalComp(FHitResult Hit);
	UStaticMeshComponent* GetMeshComp(FHitResult Hit);
	FVector GetForceToApplyVector(AActor* Actor);

	FVector GetEndVector(AController* OwnerController);

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

};
