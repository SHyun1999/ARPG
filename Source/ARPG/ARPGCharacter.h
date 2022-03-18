// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultItem.h"
#include "ARPGCharacter.generated.h"

class AWeapon;
class UMetalComponent;
class AARPGCharacterController;


USTRUCT(BluePrintType)
struct FInventory
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ADefaultItem*> ItemList;
};

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

	UFUNCTION(BlueprintCallable, Category = "item")
		void AddToInventory(ADefaultItem* _Item);
	
	//allows character to burn both bronze and copper
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	class UBronzeCopperComponent* BronzeCopperComponent;

	//allows character to burn both atium and lerasium
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	class UAtiumLerasiumComponent* AtiumLerasiumComponent;

	//allows character to burn both Duralumin and aluminum
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	class UDuraluminAluminumComponent* DuraluminAluminumComponent;

	//allows character to burn both pewter and tin
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	class UPewterTinComponent* PewterTinComponent;

	//allows character to burn both steel and iron
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	class USteelIronComponent* SteelIronComponent;

	//manages metal reserves
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	class UMetalReserveComponent* MetalReserveComponent;

	//if true, allows character to drink to refill metal reserve
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Allomancy")
	bool bHasFlask = false;

	//check if player is actively burning a toggleable metal
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	bool bIsBurningMetal = false;
	
	//check if player is hiding metal by burning copper
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	bool bIsHiddingPulses = false;

	//ratio at which metal reserves are draining passively
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float DrainingRatio = 0.1;

	//determines strong next duralumin-enhanced steelpush/ ironpull will me
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float DuraluminEnhancementMultiplier = 1;

	//last action used.
	UPROPERTY(EditAnywhere, Category = "Debugging")
	FString NameOfLastAction = "";

	//check if character has attacked
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bHasAttacked;

	//creates inventory structure
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		FInventory Inventory;

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

	//returns name of last action cast by char
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
	
	//checks if char burned duralumin
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
	//sets a delay to sync with drink animation.
	void DrinkDelay();
	//greatly enhances next allomantic skill
	void TryDuraluminFlare();

	//if GetAllomanticLines is true, pushes if >0, pulls if <0.
	void TrySteelIron(int Direction);
	template<int Direction>
	void TrySteelIron();

	// pushes(pewter) if >0, pulls(tin) if <0.
	void TryPewterTin(int Direction);
	template <int Direction>
	void TryPewterTin();

	// pushes(Atium) if >0, pulls(lerasium) if <0.
	void TryAtiumLerasium(int Direction);
	template <int Direction>
	void TryAtiumLerasium();

	template <int Direction>
	void TryDuraluminAluminum();
	void TryDuraluminAluminum(int Direction);

	template <int Direction>
	void TryBronzeSearch();
	void TryBronzeSearch(int Direction);


	//allows the character to attack
	void Attack();

	void TryDrainMetalReserves();

	//VARIABLES
	/////////////////////////////
	
	//ALLOMANCY VARIABLES
	//character's maximum metal reserve
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float MaxMetalReserve = 100.f ;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	//cost of casting steel iron
	float SteelIronActionCost = 10;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	//base cost of toggling pewter
	float PewterActionCost = 5;
	//base cost of toggling tin
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float TinActionCost = 3;
	//base cost of toggling duralumin
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float AtiumActionCost = 3;

	//draining multiplier of burning atium
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float AtiumDrainingMultiplier = 2.4f;

	//draining multiplier of burning pewter
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float PewterDrainingMultiplier = .5f;

	//draining multiplier of burning tin
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float TinDrainingMultiplier = .3f;

	//draining multiplier after cost of casting metals has been applied
	float DrainingMultiplierToApply;
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
