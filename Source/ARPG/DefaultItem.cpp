// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultItem.h"

// Sets default values
ADefaultItem::ADefaultItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemName = "item";

}

// Called when the game starts or when spawned
void ADefaultItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

