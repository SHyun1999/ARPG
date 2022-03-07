// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableMetalVialActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "ARPGCharacter.h"

// Sets default values
APickableMetalVialActor::APickableMetalVialActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);

}

// Called when the game starts or when spawned
void APickableMetalVialActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickableMetalVialActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APickableMetalVialActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AARPGCharacter* Char = Cast<AARPGCharacter>(OtherActor);
	if (Char)
	{
		Char->bHasFlask = !Char->bHasFlask;
		Destroy();
	}

}
