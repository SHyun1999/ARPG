// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllomancySkillComponent.h"
#include "BronzeCopperComponent.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UBronzeCopperComponent : public UAllomancySkillComponent
{
	GENERATED_BODY()
public:

	UBronzeCopperComponent();
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
	bool CastAction(int Direction, float DrainingMultiplier)override;

private:
	//searches for pawns within a 100 m that are burning metal
	bool SearchAllomanticPulse();
	bool BurnCopper();
	bool BurnMetal(int Direction);
	bool BurnBronze();
};
