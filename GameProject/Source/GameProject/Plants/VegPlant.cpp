// Fill out your copyright notice in the Description page of Project Settings.


#include "VegPlant.h"

AVegPlant::AVegPlant()
{

	LiveDay = 0;
	MaxDeathDay = 1;
	DeathCount = 0;
	MaxLevel = 4;



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


	if (DemoCount == Yellomelon+1) DemoCount = Tomato;

	switch (DemoCount)
	{
	case Tomato: {
		ItemName = "Tomato";
		//토마토
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FRUIT1
		(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/FinalTomato.FinalTomato'"));
		if (SM_FRUIT1.Succeeded()) {
			Meshs.Add(SM_FRUIT1.Object);

		}
		++DemoCount;

		break;

	}
	case Cucumber: {
		ItemName = "Cucumber";

		//오이
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FRUIT2
		(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/FinalCuc.FinalCuc'"));
		if (SM_FRUIT2.Succeeded()) {
			Meshs.Add(SM_FRUIT2.Object);


		}
		++DemoCount;

		break;
	}
	case Yellomelon: {
		ItemName = "Yellomelon";
		//참외아직안만듬.....
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FRUIT3
		(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/yellomelon.yellomelon'"));
		if (SM_FRUIT3.Succeeded()) {
			Meshs.Add(SM_FRUIT3.Object);

		}
		++DemoCount;

		break;
	}

	default:
		break;
	}

	//데모때 다 보여주기위해서 일단 순서대로 나오게 설정하겠슴


	Current->SetCollisionProfileName("NoCollision");

}

void AVegPlant::BeginPlay()
{
	Super::BeginPlay();
}

void AVegPlant::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
