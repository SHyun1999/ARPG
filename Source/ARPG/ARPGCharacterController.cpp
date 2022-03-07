// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGCharacterController.h"
#include "Blueprint/UserWidget.h"

// Called when the game starts or when spawned


void AARPGCharacterController::BeginPlay()
{
	Super::BeginPlay();
	UUserWidget* HUDScreen = CreateWidget(this, HUDClass);
	DebugScreen = CreateWidget(this, DebugScreenClass);

	if (HUDScreen != nullptr)
	{
		HUDScreen->AddToViewport();
	}
	if (DebugScreen != nullptr)
	{
		DebugScreen->AddToViewport();
		DebugScreen->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AARPGCharacterController::ToggleDebugScreen()
{
	bIsShowingDebugScreen = !bIsShowingDebugScreen;
	if (bIsShowingDebugScreen)
	{
		DebugScreen->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		DebugScreen->SetVisibility(ESlateVisibility::Hidden);
	}
}