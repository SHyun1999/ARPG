// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetallicObject.generated.h"

class UMetalComponent;

UCLASS()
class ARPG_API AMetallicObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMetallicObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//mesh comp
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* MeshComp;

	//is metal?
	UPROPERTY(VisibleAnywhere)
		UMetalComponent* MetalComp;
};
