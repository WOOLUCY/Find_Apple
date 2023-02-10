// Fill out your copyright notice in the Description page of Project Settings.


#include "Cloud.h"

// Sets default values
ACloud::ACloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cloud = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CLOUD"));
	Rain = CreateDefaultSubobject<UNiagaraComponent>(TEXT("RAIN"));

	Cloud->SetRelativeRotation(FRotator(0, 90.f,0.f));

	Rain->SetupAttachment(Cloud);
	Rain->SetRelativeLocation(FVector(0, 0, 118.711066f));

	const ConstructorHelpers::FObjectFinder<UStaticMesh> SM_CLOUD
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/Cloud.Cloud'"));

	if (SM_CLOUD.Succeeded()) {
		Cloud->SetStaticMesh(SM_CLOUD.Object);
	}

	//const ConstructorHelpers::FObjectFinder<UParticleSystem> NG_RAIN
	const ConstructorHelpers::FObjectFinder<UNiagaraSystem> NG_RAIN
	(TEXT("/Script/Niagara.NiagaraSystem'/Game/kaon/Particle/NG_Rain.NG_Rain'"));


	if (NG_RAIN.Succeeded()) {
		Rain->SetAsset(NG_RAIN.Object); 
	}

	Cloud->SetCollisionProfileName(TEXT("NoCollision"));

	Rain->SetCollisionProfileName(TEXT("NoCollision"));

	SetLifeSpan(3);

}

// Called when the game starts or when spawned
void ACloud::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

