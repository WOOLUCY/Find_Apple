// Fill out your copyright notice in the Description page of Project Settings.


#include "RootPlant.h"
#include "Kismet/GameplayStatics.h"


#include "../FindAppleCharacter.h"

ARootPlant::ARootPlant()
{
	LiveDay = 0;
	MaxDeathDay = 1;
	DeathCount = 0;
	MaxLevel = 3;
	IsFruit = false;

	Current = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CurrentMesh"));
	RootComponent = Current;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_VEG1
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/rootplant1.rootplant1'"));

	if (SM_VEG1.Succeeded()) {
		Meshs.Add(SM_VEG1.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_VEG2
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/rootplant2.rootplant2'"));
	if (SM_VEG2.Succeeded()) {
		Meshs.Add(SM_VEG2.Object);
	}




	switch (DemoCount)
	{
	case 0: {
		ItemName = "Radish";
		//무
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_ROOT1
		(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/rootplatn3.rootplatn3'"));
		if (SM_ROOT1.Succeeded()) {
			Meshs.Add(SM_ROOT1.Object);

		}
		break;

	}
	case 1: {
		ItemName = "Carrot";

		//당근
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_ROOT2
		(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/Carrot.Carrot'"));
		if (SM_ROOT2.Succeeded()) {
			Meshs.Add(SM_ROOT2.Object);


		}
		break;
	}
	case 2: {
		ItemName = "Kohlrabi";
		//콜라비
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_ROOT3
		(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/kohlrabi.kohlrabi'"));
		if (SM_ROOT3.Succeeded()) {
			Meshs.Add(SM_ROOT3.Object);

		}
		break;
	}
	case 3: {
		ItemName = "Watermelon";
		//수박
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_ROOT4
		(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/Watermelon1.Watermelon1'"));
		if (SM_ROOT4.Succeeded()) {
			Meshs.Add(SM_ROOT4.Object);

		}
		break;
	}

	default:
		break;
	}

	//데모때 다 보여주기위해서 일단 순서대로 나오게 설정하겠슴
	++DemoCount;
	if (DemoCount == TOTAL) DemoCount = 0;
	

	Current->SetCollisionProfileName("NoCollision");

}

void ARootPlant::BeginPlay()
{
	Super::BeginPlay();



}

void ARootPlant::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	DemoCount = 0;

}

