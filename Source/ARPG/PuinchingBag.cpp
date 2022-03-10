// Fill out your copyright notice in the Description page of Project Settings.


#include "PuinchingBag.h"

// Sets default values
APuinchingBag::APuinchingBag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;

}

// Called when the game starts or when spawned
void APuinchingBag::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuinchingBag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuinchingBag::TakeDamage(float _DamageToTake)
{
	_DamageToTake = FMath::Min(CurrentHealth, _DamageToTake);
	CurrentHealth -= _DamageToTake;
}

float APuinchingBag::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}