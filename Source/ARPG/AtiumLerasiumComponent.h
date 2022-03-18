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

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool BurnMetal(int Direction);
	//modifies speed of world based on which metal is being burned
	void BurnAtiumLerasium(float TimeDilation, float CustomTimeDilation);

	//makes world slower
	const float AtiumTimeDilation = .35f;
	//makes player move at normal speed
	const float AtiumCustomTime = 2.6f;
	//makes world move faster
	const float LerasiumTimeDilation = 1.55f;

};
