// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllomancySkillComponent.h"
#include "DuraluminAluminumComponent.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UDuraluminAluminumComponent : public UAllomancySkillComponent
{
	GENERATED_BODY()
	
public:
	void SetDuraluminEnhancement();
	void DrainMetalReserves();
};
