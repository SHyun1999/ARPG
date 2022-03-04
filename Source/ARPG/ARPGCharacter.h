// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARPGCharacter.generated.h"

class AWeapon;

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

private:
	void MoveForward(float AxisValue);
	void MoveSide(float AxisValue);
	void LookUp(float AxisValue);
	void LookSide(float AxisValue);

	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	//ACTIONS
	void SteelPush();
	void IronPull();
	bool GetAllomanticLines(FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float TraceDistance = 2000.f;
	UPROPERTY(EditAnywhere, Category = "Allomancy")
	float ImpulseForce = 100.f;


	UPROPERTY(EditAnywhere)
	float RotationRate = 10;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY()
	AWeapon* Weapon;

	

};
