// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllomancySkillComponent.h"
#include "AtiumLerasiumComponent.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UAtiumLerasiumComponent : public UAllomancySkillComponent
{
	GENERATED_BODY()
	UAtiumLerasiumComponent();
public:
	bool CastAction(int Direction, float DrainingMultiplier)override;

private:
	bool BurnMetal(int Direction);

};
