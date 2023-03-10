// Fill out your copyright notice in the Description page of Project Settings.


#include "Tomato.h"

ATomato::ATomato()
{
	LiveDay = 0;
	MaxDeathDay = 1;
	DeathCount = 0;
	IsFruit = true;
	
	Current = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CurrentMesh"));
	RootComponent = Current;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_VEG1
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/vegetation01.vegetation01'"));
	
	if (SM_VEG1.Succeeded()) {
		Meshs.Add(SM_VEG1.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_VEG2
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/vegetation02.vegetation02'"));
	if (SM_VEG2.Succeeded()) {
		Meshs.Add(SM_VEG2.Object);
	}

	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_VEG3
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/vegetation03.vegetation03'"));
	if (SM_VEG3.Succeeded()) {
		Meshs.Add(SM_VEG3.Object);
	}

	Current->SetCollisionProfileName("NoCollision");
}



void ATomato::BeginPlay()
{
	Super::BeginPlay();

	
}

