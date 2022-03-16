// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGCharacter.h"
#include "Weapon.h"
#include "ARPGCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "MetalReserveComponent.h"
#include "AllomancySkillComponent.h"
#include "SteelIronComponent.h"
#include "PewterTinComponent.h"
#include "DuraluminAluminumComponent.h"
#include "AtiumLerasiumComponent.h"

// Sets default values
AARPGCharacter::AARPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MetalReserveComponent = CreateDefaultSubobject<UMetalReserveComponent>(TEXT("Metal reserve component"));
	AddOwnedComponent(MetalReserveComponent);

	SteelIronComponent = CreateDefaultSubobject<USteelIronComponent>(TEXT("Steel Iron component"));
	AddOwnedComponent(SteelIronComponent);

	PewterTinComponent = CreateDefaultSubobject<UPewterTinComponent>(TEXT("Pewter Tin component"));
	AddOwnedComponent(PewterTinComponent);

	DuraluminAluminumComponent = CreateDefaultSubobject<UDuraluminAluminumComponent>(TEXT("Duralumin Aluminum component"));
	AddOwnedComponent(DuraluminAluminumComponent);

	AtiumLerasiumComponent = CreateDefaultSubobject<UAtiumLerasiumComponent>(TEXT("Atium Lerasium component"));
	AddOwnedComponent(AtiumLerasiumComponent);

	bHasAttacked = false;
	CharController = Cast<AARPGCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called when the game starts or when spawned
void AARPGCharacter::BeginPlay()
{
	Super::BeginPlay();

	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Weapon->SetOwner(this);

	CurrentMetalReserve = MaxMetalReserve;
	
}

// Called every frame
void AARPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MetalReserveComponent->ReduceMetalReserve(DrainingRatio * DeltaTime);


	if (bIsBurningMetal && !TryCanCastAllomanticAction(PewterActionCost))
	{
		ResetStrValue();
		TryResetDrainingRatio();
		bIsBurningMetal = !bIsBurningMetal;
	}
}

// Called to bind functionality to input
void AARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//AXIS
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AARPGCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &AARPGCharacter::MoveSide);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AARPGCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookSide"), this, &AARPGCharacter::LookSide);

	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AARPGCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AARPGCharacter::LookRightRate);

	//ACTIONS
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("SteelPush"), EInputEvent::IE_Pressed, this, &AARPGCharacter::TrySteelIron<1>);
	PlayerInputComponent->BindAction(TEXT("IronPull"), EInputEvent::IE_Pressed, this, &AARPGCharacter::TrySteelIron<-1>);
	PlayerInputComponent->BindAction(TEXT("PewterBurn"), EInputEvent::IE_Pressed, this, &AARPGCharacter::TryPewterTin<1>);
	PlayerInputComponent->BindAction(TEXT("TinBurn"), EInputEvent::IE_Pressed, this, &AARPGCharacter::TryPewterTin<-1>);
	PlayerInputComponent->BindAction(TEXT("AtiumBurn"), EInputEvent::IE_Pressed, this, &AARPGCharacter::TryAtiumLerasium<1>);
	PlayerInputComponent->BindAction(TEXT("LerasiumBurn"), EInputEvent::IE_Pressed, this, &AARPGCharacter::TryAtiumLerasium<-1>);
	PlayerInputComponent->BindAction(TEXT("DuraluminFlare"), EInputEvent::IE_Pressed, this, &AARPGCharacter::TryDuraluminAluminum<1>);
	PlayerInputComponent->BindAction(TEXT("AluminumFlare"), EInputEvent::IE_Pressed, this, &AARPGCharacter::TryDuraluminAluminum<-1>);
	PlayerInputComponent->BindAction(TEXT("DrinkVial"), EInputEvent::IE_Pressed, this, &AARPGCharacter::DrinkDelay);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AARPGCharacter::Attack);

	//DEBUGGING SCREEN
	PlayerInputComponent->BindAction(TEXT("ToggleDebuggingScreen"), EInputEvent::IE_Pressed, this, &AARPGCharacter::ToggleDebuggingScreen);

}

//////////////////////////////////////MOVEMENT
/////////////////////////////////////////////////////////////////////////
void AARPGCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AARPGCharacter::MoveSide(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AARPGCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AARPGCharacter::LookSide(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AARPGCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AARPGCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

//////////////////////////////////////ABILITIES
/////////////////////////////////////////////////////////////////////////

template <int Direction>
void AARPGCharacter::TrySteelIron()
{
	NameOfLastAction = __func__;
	TrySteelIron(Direction);
}

void AARPGCharacter::TrySteelIron(int Direction)
{
	if (!bDuraluminFlare)
	{
		if (!TryCanCastAllomanticAction(SteelIronActionCost)) { bLastActionSuccess = false;  return; };
	}
	if (!SteelIronComponent->CastAction(Direction, 0.f)) { bLastActionSuccess = false;  return; };
	bDuraluminFlare = false;
	bLastActionSuccess = true;
	MetalReserveComponent->ReduceMetalReserve(SteelIronActionCost);

}


template <int Direction>
void AARPGCharacter::TryDuraluminAluminum()
{
	NameOfLastAction = __func__;
	TryDuraluminAluminum(Direction);
}

void AARPGCharacter::TryDuraluminAluminum(int Direction)
{
	if (!TryCanCastAllomanticAction(SteelIronActionCost)) { bLastActionSuccess = false;  return; };
	bLastActionSuccess = true;
	if (Direction < 0) 
	{
		DuraluminAluminumComponent->DrainMetalReserves();
	}
	if (Direction >= 0)
	{
		bDuraluminFlare = !bDuraluminFlare;
		
	}
	if (bDuraluminFlare)
	{
		DuraluminAluminumComponent->SetDuraluminEnhancement();
		DuraluminAluminumComponent->DrainMetalReserves();
	}
}

template <int Direction>
void AARPGCharacter::TryPewterTin()
{
	NameOfLastAction = __func__;
	TryPewterTin(Direction);
}


void AARPGCharacter::TryPewterTin(int Direction)
{
	float MetalToBurn;
	if (Direction < 0)
	{
		MetalToBurn = PewterActionCost;
		DrainingMultiplierToApply = PewterDrainingMultiplier;
	}else
	{
		DrainingMultiplierToApply = TinDrainingMultiplier;
		MetalToBurn = TinActionCost;
	}

	if (!TryCanCastAllomanticAction(MetalToBurn)) { bLastActionSuccess = false;  return; };
	bIsBurningMetal = !bIsBurningMetal;

	if (bIsBurningMetal) 
	{
		MetalReserveComponent->ReduceMetalReserve(MetalToBurn); //only reduce metal when starting action, not when cancelling it.
	}
	PewterTinComponent->CastAction(Direction, DrainingMultiplierToApply);
	bLastActionSuccess = true;
}

template <int Direction>
void AARPGCharacter::TryAtiumLerasium()
{
	NameOfLastAction = __func__;
	TryAtiumLerasium(Direction);
}

void AARPGCharacter::TryAtiumLerasium(int Direction)
{
	float MetalToBurn;
	if (Direction < 0)
	{
		DrainingMultiplierToApply = TinDrainingMultiplier; // TODO CHANGE TO LERASIUM VALUES
		MetalToBurn = TinActionCost;
	}
	else
	{
		MetalToBurn = AtiumActionCost;
		DrainingMultiplierToApply = AtiumDrainingMultiplier;
	}

	if (!TryCanCastAllomanticAction(MetalToBurn)) { bLastActionSuccess = false;  return; };
	bIsBurningMetal = !bIsBurningMetal;

	if (bIsBurningMetal)
	{
		MetalReserveComponent->ReduceMetalReserve(MetalToBurn); //only reduce metal when starting action, not when cancelling it.
	}
	AtiumLerasiumComponent->CastAction(Direction, DrainingMultiplierToApply);
	bLastActionSuccess = true;
}

void AARPGCharacter::Attack()
{
	bHasAttacked = true;
}

float AARPGCharacter::GetDuraluminEnhancement() const 
{
	return DuraluminEnhancementMultiplier;
}

void AARPGCharacter::ResetStrValue()
{
	STR = 10;
}

//////////////////////////////////////METAL RESERVES
/////////////////////////////////////////////////////////////////////////

void AARPGCharacter::TryResetDrainingRatio() 
{
	MetalReserveComponent->ResetDrainingRatio();
}

float AARPGCharacter::TryGetMetalReservePercent() const
{
	return MetalReserveComponent->GetMetalReservePercent();
}

void AARPGCharacter::TryReduceMetalReserve(float QuantToRemove)
{
	MetalReserveComponent->ReduceMetalReserve(QuantToRemove);
}

bool AARPGCharacter::TryCanCastAllomanticAction(int ActionCost)
{
	return MetalReserveComponent->CanCastAllomanticAction(ActionCost);
}

void AARPGCharacter::TryDrainMetalReserves()
{
	MetalReserveComponent->DrainMetalReserves();
}

bool AARPGCharacter::CanDrinkVial()
{
	return bHasFlask && CurrentMetalReserve < MaxMetalReserve;
}

void AARPGCharacter::DrinkVial()
{
	CurrentMetalReserve = MaxMetalReserve;
	bHasFlask = !bHasFlask;
}

void AARPGCharacter::DrinkDelay()
{
	if (CanDrinkVial())
	{
		GetWorldTimerManager().SetTimer(
			UnusedHandle, this, &AARPGCharacter::DrinkVial, TimerDelay, false);
	}
}

//////////////////////////////////////DEBUGGING
/////////////////////////////////////////////////////////////////////////
float AARPGCharacter::GetMetalReserve()const
{
	return CurrentMetalReserve;
}

bool AARPGCharacter::IsBurningMetal()const
{
	return bIsBurningMetal;
}

float AARPGCharacter::GetDrainingRatio()const
{
	return DrainingRatio;
}

bool AARPGCharacter::IsBurningDuralumin()const
{
	return bDuraluminFlare;
}

void AARPGCharacter::ToggleDebuggingScreen()
{
	if (CharController)
	{
		CharController->ToggleDebugScreen();
	}
}

FString AARPGCharacter::GetLastAction()
{
	return NameOfLastAction;
}

bool AARPGCharacter::CouldCastAction()
{
	return bLastActionSuccess;
}

//////////////////////////////////////STATS
/////////////////////////////////////////////////////////////////////////

float AARPGCharacter::GetSTR()
{
	return STR;
}

bool AARPGCharacter::setSTR(float NewSTR)
{
	STR = NewSTR;
	return true;
}