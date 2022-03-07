// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGCharacter.h"
#include "Weapon.h"
#include "AllomanticComponent.h"
#include "ARPGCharacterController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AARPGCharacter::AARPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AllomanticComponent = CreateDefaultSubobject<UAllomanticComponent>(TEXT("Allomantic component"));
	AddOwnedComponent(AllomanticComponent);


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

	ReduceMetalReserve(DrainingRatio * DeltaTime);


	if (bIsBurningMetal && !CanCastAllomanticAction(PewterActionCost))
	{
		ResetStrValue();
		ResetDrainingRatio();
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
	PlayerInputComponent->BindAction(TEXT("PewterBurn"), EInputEvent::IE_Pressed, this, &AARPGCharacter::TryBurnMetal);
	PlayerInputComponent->BindAction(TEXT("DrinkVial"), EInputEvent::IE_Pressed, this, &AARPGCharacter::DrinkDelay);

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
	TrySteelIron(Direction);
}

void AARPGCharacter::TrySteelIron(int Direction)
{
	if (!CanCastAllomanticAction(SteelIronActionCost)) return;
	if (!AllomanticComponent->SteelIron(Direction)) return;
	ReduceMetalReserve(SteelIronActionCost);
}

void AARPGCharacter::TryBurnMetal()
{
	if (!CanCastAllomanticAction(PewterActionCost)) return;
	bIsBurningMetal = !bIsBurningMetal;

	if (bIsBurningMetal) {
		ReduceMetalReserve(PewterActionCost); //only reduce metal when starting action, not when cancelling it.
	}
	AllomanticComponent->BurnMetal();
	
}

void AARPGCharacter::ResetDrainingRatio() 
{
	DrainingRatio = 0.1;
}

void AARPGCharacter::ResetStrValue()
{
	STR = 10;
}

//////////////////////////////////////METAL RESERVES
/////////////////////////////////////////////////////////////////////////
float AARPGCharacter::GetMetalReservePercent() const
{
	return CurrentMetalReserve / MaxMetalReserve;
}

void AARPGCharacter::ReduceMetalReserve(float QuantToRemove)
{
	QuantToRemove = FMath::Min(CurrentMetalReserve, QuantToRemove);
	CurrentMetalReserve -= QuantToRemove;
}

bool AARPGCharacter::CanCastAllomanticAction(int ActionCost)
{
	return ActionCost < CurrentMetalReserve;
}

bool AARPGCharacter::CanDrinkVial()
{
	return bHasFlask && CurrentMetalReserve< MaxMetalReserve;
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


//////////////////////////////////////METAL RESERVES
/////////////////////////////////////////////////////////////////////////
void AARPGCharacter::ToggleDebuggingScreen()
{
	if (CharController)
	{
		CharController->ToggleDebugScreen();
	}
}