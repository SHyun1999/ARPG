// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingActor.h"

// Sets default values
AMovingActor::AMovingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		FVector NewLocation = GetActorLocation();
		float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

		NewLocation.Z += DeltaHeight * 300.0f;
		RunningTime += DeltaTime;
		SetActorLocation(NewLocation);
	}

}

