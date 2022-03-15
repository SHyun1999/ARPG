// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllomancySkillComponent.h"
#include "SteelIronComponent.generated.h"

UCLASS()
class ARPG_API USteelIronComponent : public UAllomancySkillComponent
{
	GENERATED_BODY()
	// Sets default values for this character's properties
	USteelIronComponent();

public:
	virtual bool CastAction(int Direction) override;
	bool SteelIron(int Direction);
private:
	bool TraceAllomanticLines(FHitResult& Hit);
	bool EnhancedSteelIron(int Direction);
};
