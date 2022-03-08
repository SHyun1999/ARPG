// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGCharacter.generated.h"

class AWeapon;
class UMetalComponent;
class  AARPGCharacterController;

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
	bool CanCastAllomanticAction(int ActionCost);
	//checks if player can drink metal flask.
	UFUNCTION(BlueprintPure)
	bool CanDrinkVial();
	//fills metal reserves
	void DrinkVial();
	//resets draining ratio value. TODO: Set variable
	void ResetDrainingRatio();
	//resets draining ratio value. TODO: Set variable
	void ResetStrValue();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	class UAllomanticComponent* AllomanticComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	bool bHasFlask = false;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	bool bIsBurningMetal = false;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float DrainingRatio = 0.1;

<<<<<<< HEAD
	//returns current metal reserve
	UFUNCTION(BlueprintPure)
		float GetMetalReserve()const;

	//checks if currently burning metal
	UFUNCTION(BlueprintPure)
		bool IsBurningMetal()const;

	//returns burning ratio
	UFUNCTION(BlueprintPure)
		float GetDrainingRatio()const;

=======
>>>>>>> parent of d00ae34 (bind location, rotation, burning metals to debugging screen)
	//STATS VARIABLES
	float STR = 10;
private:

	//FUNCTIONS
	/////////////////////////////

	//DEBUGGING
	void ToggleDebuggingScreen();
	
	// MOVEMENT FUNCTIONS
	void MoveForward(float AxisValue);
	void MoveSide(float AxisValue);
	void LookUp(float AxisValue);
	void LookSide(float AxisValue);

	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	//ACTION FUNCTIONS
	//if GetAllomanticLines is true, pushes if >0, pulls if <0.
	void ReduceMetalReserve(float QuantToRemove);
	void TrySteelIron(int Direction);
	template<int Direction>
	void TrySteelIron();
	//sets a delay to sync with drink animation.
	void DrinkDelay();

	//calls AllomanticComponent->PewterBurn
	void TryBurnMetal();
	//VARIABLES
	/////////////////////////////
	
	//ALLOMANCY VARIABLES
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float MaxMetalReserve = 100.f ;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float CurrentMetalReserve;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float SteelIronActionCost = 10;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float PewterActionCost = 10;

	//MOVEMENT VARIABLES
	UPROPERTY(EditAnywhere)
	float RotationRate = 10;

	//DRINK DELAY VARIABLES
	float TimerDelay = 4.5;
	FTimerHandle UnusedHandle;

	//WEAPON VARIABLES
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY()
	AWeapon* Weapon;

	//DEBUGGING
	AARPGCharacterController* CharController;
	

};
