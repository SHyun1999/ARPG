// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGCharacter.generated.h"

class AWeapon;
class UMetalComponent;
class AARPGCharacterController;

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
	float TryGetMetalReservePercent() const;
	//returns Duralumin enhancement multiplier
	UFUNCTION(BlueprintPure)
	float GetDuraluminEnhancement() const;
	// checks if enough to cast allomantic ability.
	bool TryCanCastAllomanticAction(int ActionCost);
	//checks if player can drink metal flask.
	UFUNCTION(BlueprintPure)
	bool CanDrinkVial();
	//fills metal reserves
	void DrinkVial();
	//resets draining ratio value.
	void TryResetDrainingRatio();
	//resets draining ratio value.
	void ResetStrValue();
	// multiplies current reserves by .03
	void TrySetDuraluminEnhancement();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	class UDuraluminAluminumComponent* DuraluminAluminumComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	class UPewterTinComponent* PewterTinComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	class USteelIronComponent* SteelIronComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	class UAllomanticComponent* AllomanticComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	class UMetalReserveComponent* MetalReserveComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	bool bHasFlask = false;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	bool bIsBurningMetal = false;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float DrainingRatio = 0.1;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float DuraluminEnhancementMultiplier = 1;
	UPROPERTY(EditAnywhere, Category = "Debugging")
	FString NameOfLastAction = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bHasAttacked;


	//returns current metal reserve
	UFUNCTION(BlueprintPure)
	float GetMetalReserve()const;

	//checks if currently burning metal
	UFUNCTION(BlueprintPure)
	bool IsBurningMetal()const;

	UFUNCTION(BlueprintPure)
	bool IsBurningDuralumin()const;

	//returns burning ratio
	UFUNCTION(BlueprintPure)
	float GetDrainingRatio()const;

	UFUNCTION(BlueprintPure)
	FString GetLastAction();
	UFUNCTION(BlueprintPure)
	bool CouldCastAction();
	
	//returns strength value
	UFUNCTION(BlueprintPure)
	float GetSTR();

	//sets strength value
	UFUNCTION(BlueprintPure)
	bool setSTR(float NewSTR);
	

	UPROPERTY(EditAnywhere, Category = "Allomancy")
	bool bDuraluminFlare = false;

	//STATS VARIABLES
	UPROPERTY(EditAnywhere, Category="Combat")
	float STR = 10;

	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float CurrentMetalReserve;

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
	void TryReduceMetalReserve(float QuantToRemove);
	//if GetAllomanticLines is true, pushes if >0, pulls if <0.
	void TrySteelIron(int Direction);
	template<int Direction>
	void TrySteelIron();
	//sets a delay to sync with drink animation.
	void DrinkDelay();
	//greatly enhances next allomantic skill
	void TryDuraluminFlare();

	//calls AllomanticComponent->BurnMetal. pushes(pewter) if >0, pulls(tin) if <0.
	void TryBurnMetal(int Direction);
	template <int Direction>
	void TryBurnMetal();

	template <int Direction>
	void TryDuraluminAluminum();
	void TryDuraluminAluminum(int Direction);


	//allows the character to attack
	void Attack();

	void TryDrainMetalReserves();

	//VARIABLES
	/////////////////////////////
	
	//ALLOMANCY VARIABLES
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float MaxMetalReserve = 100.f ;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float SteelIronActionCost = 10;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float PewterActionCost = 5;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float TinActionCost = 3;


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
	bool bLastActionSuccess;
	

};
