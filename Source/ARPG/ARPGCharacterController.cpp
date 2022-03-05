// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGCharacterController.h"
#include "Blueprint/UserWidget.h"

// Called when the game starts or when spawned


void AARPGCharacterController::BeginPlay()
{
	Super::BeginPlay();
	UUserWidget* HUDScreen = CreateWidget(this, HUDClass);
	if (HUDScreen != nullptr)
	{
		HUDScreen->AddToViewport();
	}
}