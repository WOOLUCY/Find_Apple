// Fill out your copyright notice in the Description page of Project Settings.


#include "FishingRod.h"

// Sets default values
AFishingRod::AFishingRod()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Rod = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Rod;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_MESH
	(TEXT("/Script/Engine.StaticMesh'/Game/Woo/Rod/Rod.Rod'"));
	if (SM_MESH.Succeeded()) {
		Rod->SetStaticMesh(SM_MESH.Object);
	}

	Rod->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void AFishingRod::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFishingRod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFishingRod::SetRodVisibility(bool _in)
{
	Rod->SetVisibility(_in);
}

