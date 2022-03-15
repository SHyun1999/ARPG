// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllomancySkillComponent.h"
#include "PewterTinComponent.generated.h"

/**
 *
 */
UCLASS()
class ARPG_API UPewterTinComponent : public UAllomancySkillComponent
{
	GENERATED_BODY()

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//sets which metal is being burned.
	bool BurnMetal(int Direction);
	//increases metal burn rate, multiplies strength attribute.
	void BurnPewter();
	//HIGHLIGHTS which items allomancy can interact with
	void BurnTin();
private:

	bool bIsBurningTin = false;
	void TraceTinLines();

};
