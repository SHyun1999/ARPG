// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGCharacter.h"
#include "Weapon.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MetalComponent.h"

// Sets default values
AARPGCharacter::AARPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AARPGCharacter::BeginPlay()
{
	Super::BeginPlay();

	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Weapon->SetOwner(this);
	
}

// Called every frame
void AARPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	PlayerInputComponent->BindAction(TEXT("SteelPush"), EInputEvent::IE_Pressed, this, &AARPGCharacter::SteelPush);
	PlayerInputComponent->BindAction(TEXT("IronPull"), EInputEvent::IE_Pressed, this, &AARPGCharacter::IronPull);

	//PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharARPGCharacteracter::Shoot);

}

//MOVEMENT
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

//ABILITIES
FVector AARPGCharacter::GetForceToApplyVector()
{
	return this->GetActorForwardVector() * ImpulseForce;
}

UMetalComponent* AARPGCharacter::GetMetalComp(FHitResult Hit)
{
	return Cast<UMetalComponent>(Hit.GetActor()->FindComponentByClass<UMetalComponent>());
}

UStaticMeshComponent* AARPGCharacter::GetMeshComp(FHitResult Hit) 
{
	return Cast<UStaticMeshComponent>(Hit.GetActor()->GetRootComponent());
}

bool AARPGCharacter::GetAllomanticLines(FHitResult& Hit)
{

	const FVector Start = GetActorLocation();
	
	FCollisionQueryParams TraceParams;

	AController* OwnerController = GetController();
	if (OwnerController == nullptr) return false;
	FVector Loc;
	FRotator Rot;
	OwnerController->GetPlayerViewPoint(Loc, Rot);//these are out params
	
	FVector End = Loc + Rot.Vector() * TraceDistance;
	TraceParams.AddIgnoredActor(this);
	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, .5f);
	return GetWorld()->LineTraceSingleByChannel(Hit,
										Start,
										End,
										ECollisionChannel::ECC_Visibility, // check defaultengine.ini file to get bullet collision channel
										TraceParams); 
}


void AARPGCharacter::SteelPush()
{
	FHitResult Hit;

	if (GetAllomanticLines(Hit))
	{
		UStaticMeshComponent* MeshComponent = GetMeshComp(Hit);
		UMetalComponent* MetalComponent = GetMetalComp(Hit);
		if (MetalComponent && MeshComponent && Hit.GetActor()->IsRootComponentMovable()) //Check if is metal, and exists, and is movable.
		{
			if (MetalComponent->bIsAlluminum) return; //allomancy doesn't affect alluminum!
			MeshComponent->AddImpulse(GetForceToApplyVector() * GetMesh()->GetMass());
			ACharacter::LaunchCharacter(GetForceToApplyVector() * MeshComponent->GetMass() * -1, false, true);
		}
	}

}

void AARPGCharacter::IronPull()
{
	FHitResult Hit;

	if (GetAllomanticLines(Hit))
	{
		UStaticMeshComponent* MeshComponent = GetMeshComp(Hit);
		UMetalComponent* MetalComponent = GetMetalComp(Hit);
		if (MetalComponent && MeshComponent && Hit.GetActor()->IsRootComponentMovable())  //Check if is metal, and exists, and is movable.
		{
			if (MetalComponent->bIsAlluminum) return; //allomancy doesn't affect alluminum!
			MeshComponent->AddImpulse(GetForceToApplyVector() * GetMesh()->GetMass() * -1);
			ACharacter::LaunchCharacter(GetForceToApplyVector() * MeshComponent->GetMass() , false, true);
		}
	}

}