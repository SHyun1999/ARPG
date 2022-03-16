// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuinchingBag.generated.h"

UCLASS()
class ARPG_API APuinchingBag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuinchingBag();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float _Damage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStats")
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere, Category = "EnemyStats")
	bool bIsMoving = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStats")
	float CurrentHealth;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	float RunningTime;

};
