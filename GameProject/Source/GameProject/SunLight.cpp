// Fill out your copyright notice in the Description page of Project Settings.


#include "SunLight.h"

// Sets default values
ASunLight::ASunLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sun = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("SunLight"));
	RootComponent = Sun;
	
	Sky = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sky"));
	Sky->SetRelativeScale3D(FVector(25.f, 25.f, 25.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SKY
	(TEXT("/Script/Engine.StaticMesh'/Engine/EngineSky/SM_SkySphere.SM_SkySphere'"));

	if (SM_SKY.Succeeded()) {
		Sky->SetStaticMesh(SM_SKY.Object);
		
	}


	static ConstructorHelpers::FObjectFinder<UMaterialInstance> M_DAY
	(TEXT("/Script/Engine.MaterialInstanceConstant'/Engine/MapTemplates/Sky/M_Procedural_Sky_Daytime.M_Procedural_Sky_Daytime'"));
	if (M_DAY.Succeeded()) {
		MDay = M_DAY.Object;
		Sky->SetMaterial(0, M_DAY.Object);

	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> M_NIGHT
	(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/kaon/M_Procedural_Sky_Night.M_Procedural_Sky_Night'"));
	if (M_NIGHT.Succeeded()) {
		MNight = M_NIGHT.Object;
	//	Sky->SetMaterial(0, M_NIGHT.Object);

	}
	IsNight = false;

}

// Called when the game starts or when spawned
void ASunLight::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ASunLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!IsNight) {
		Sun->AddLocalRotation(FRotator(DeltaTime, 0, 0));

		if (Sun->GetComponentRotation().Equals(FRotator(0, 0, 0),1.f)) {//나이트
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("sunset"));
			Sunset();
			Sun->SetWorldRotation(FRotator(-90, 0, 0));
			IsNight = true;
		}
		//FORCEINLINE TRotator<T>::TRotator(T InPitch, T InYaw, T InRoll)

		else if (Sun->GetComponentRotation().Equals(FRotator(0, 180, 180))) {//데이
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Sunrise"));
			//(Pitch = 0.000000, Yaw = 180.000000, Roll = 180.000000)
			Sunrise();
		}
	}
	else {
		Sky->AddLocalRotation(FRotator(0, DeltaTime, 0));
	}
}

void ASunLight::Sunset()
{
	Sun->SetIntensity(0.2f);
	Sun->SetLightFColor(FColor(73,101,179,255)); //B=179,G=101,R=73,A=255)
	Sky->SetMaterial(0, MNight);

}

void ASunLight::Sunrise()
{
	//Sun->SetIntensity(10.f);
	Sky->SetMaterial(0, MDay);

}

