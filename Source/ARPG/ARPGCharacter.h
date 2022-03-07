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
	// checks if enough to cast allomantic ability.
	bool CanCastAllomanticAction();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	class UAllomanticComponent* AllomanticComponent;

	bool bHasFlask = false;

private:
	void MoveForward(float AxisValue);
	void MoveSide(float AxisValue);
	void LookUp(float AxisValue);
	void LookSide(float AxisValue);

	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	void ReduceMetalReserve(float QuantToRemove);

	//ACTIONS

	//if GetAllomanticLines is true, pushes if >0, pulls if <0.
	void TrySteelIron(int Direction);
	template<int Direction>
	void TrySteelIron();

	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float MaxMetalReserve = 100.f;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float CurrentMetalReserve;

	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float AllomanticActionCost = 10;

	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float DrainingRatio = 0.001;


	UPROPERTY(EditAnywhere)
	float RotationRate = 10;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY()
	AWeapon* Weapon;
	

};
