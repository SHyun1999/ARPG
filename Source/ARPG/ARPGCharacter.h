// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGCharacter.generated.h"

class AWeapon;
class UMetalComponent;

UCLASS()
class ARPG_API AARPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARPGCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//returns percentage of metal reserves.
	UFUNCTION(BlueprintPure)
	float GetMetalReservePercent() const;

private:
	void MoveForward(float AxisValue);
	void MoveSide(float AxisValue);
	void LookUp(float AxisValue);
	void LookSide(float AxisValue);

	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	void ReduceMetalReserve(float QuantToRemove);

	//ACTIONS
	// checks if enough to cast allomantic ability.
	bool CanCastAllomanticAction();
	//traces a line from the player's perspective, returns true if the line traced connects with a moveable object.
	bool GetAllomanticLines(FHitResult& Hit);
	// returns forward vector multiplied by ImpulseForce
	FVector GetForceToApplyVector();
	//if GetAllomanticLines is true, pushes the object and the player on opposite directions. Dependent on the mass.
	void SteelPush();
	//if GetAllomanticLines is true, pulls the object and the player toward each other. Dependent on the mass.
	void IronPull();
	//returns metal component of the hit object.
	UMetalComponent* GetMetalComp(FHitResult Hit);
	//return static mesh component of the hit object.
	UStaticMeshComponent* GetMeshComp(FHitResult Hit);

	//if GetAllomanticLines is true, pushes if >0, pulls if <0.
	void SteelIron(int Direction);
	template<int Direction>
	void SteelIron();


	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float TraceDistance = 2000.f;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float ImpulseForce = 150.f;

	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float MaxMetalReserve = 100.f;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float CurrentMetalReserve;

	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float AllomanticActionCost = 10;

	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float DrainingRatio = 0.1;

	UPROPERTY(EditAnywhere)
	float RotationRate = 10;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY()
	AWeapon* Weapon;

	

};
