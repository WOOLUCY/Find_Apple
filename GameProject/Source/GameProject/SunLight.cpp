// Fill out your copyright notice in the Description page of Project Settings.


#include "SunLight.h"
#include "TimerHandler.h"
#include "Kismet/GameplayStatics.h"

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

	}
	IsNight = false;

}

// Called when the game starts or when spawned
void ASunLight::BeginPlay()
{
	Super::BeginPlay();
	

	TArray<AActor*> TimeOfDayHandler;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATimerHandler::StaticClass(), TimeOfDayHandler);

	if (TimeOfDayHandler.Num() !=0){
		
		GameTimer = Cast<ATimerHandler>(TimeOfDayHandler[0]);
	}
}

// Called every frame
void ASunLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//static float sum = 0;

	if (Sun->GetComponentRotation().Equals(FRotator(0, 0, 0),0.5f)) {
		//UE_LOG(LogTemp, Warning, TEXT("%f"), sum);
		SetNight();
	}

	if (IsNight && GameTimer->Today.GetHours() == 20) {
		Sun->SetIntensity(6.f);
		Sun->LightingChannels.bChannel0 = false;
	}
	if (IsNight && GameTimer->Today.GetHours() == 8  ) {
		Sunrise();
	}
	

	if (!IsNight) {
		Sun->AddLocalRotation(GameTimer->SunRotation);
	}
	else {
		Sky->AddLocalRotation(FRotator(0, DeltaTime, 0));
	}
}



void ASunLight::Sunrise()
{
	UE_LOG(LogTemp, Warning, TEXT("SUNRISZE"));

	IsNight = false;		
	Sun->LightingChannels.bChannel0 = true;
	Sky->SetMaterial(0, MDay);
	Sun->SetLightFColor(FColor(255.f,255.f,255.f,255.f));
	GameTimer->SunRotation = FRotator(BasicRot);
	Sun->SetWorldRotation(GameTimer->SunRotation);
	Sun->SetIntensity(10.f);

}


void ASunLight::SetNight()
{
	IsNight = true;
	GameTimer->SunRotation = FRotator(-90.f, 0, 0);

	Sun->SetWorldRotation(GameTimer->SunRotation);
	Sun->SetIntensity(4.f);
	Sun->SetLightFColor(BlueColor); //B=179,G=101,R=73,A=255)
	Sky->SetMaterial(0, MNight);



}

