// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ARPGCharacterController.generated.h"

class UUSerWidget;
/**
 * 
 */
UCLASS()
class ARPG_API AARPGCharacterController : public APlayerController
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	bool bIsShowingDebugScreen = false;

	//enables or disables debugging screen
	void ToggleDebugScreen();

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> DebugScreenClass;

	UUserWidget* DebugScreen;

};