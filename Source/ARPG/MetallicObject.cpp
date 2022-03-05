// Fill out your copyright notice in the Description page of Project Settings.


#include "MetallicObject.h"
#include "MetalComponent.h"

// Sets default values
AMetallicObject::AMetallicObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	SetRootComponent(MeshComp);

	MetalComp = CreateDefaultSubobject<UMetalComponent>(TEXT("MetalComp"));
}

// Called when the game starts or when spawned
void AMetallicObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMetallicObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

