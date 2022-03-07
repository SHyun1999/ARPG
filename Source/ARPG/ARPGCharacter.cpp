// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGCharacter.h"
#include "Weapon.h"
#include "AllomanticComponent.h"


// Sets default values
AARPGCharacter::AARPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AllomanticComponent = CreateDefaultSubobject<UAllomanticComponent>(TEXT("Allomantic component"));
	AddOwnedComponent(AllomanticComponent);

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
	if (!CanCastAllomanticAction()) return;
	if (!AllomanticComponent->SteelIron(Direction)) return;
	ReduceMetalReserve(AllomanticActionCost);
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

bool AARPGCharacter::CanCastAllomanticAction()
{
	return AllomanticActionCost < CurrentMetalReserve;
}