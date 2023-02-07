// Fill out your copyright notice in the Description page of Project Settings.


#include "Tomato.h"
#include "TimerHandler.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATomato::ATomato()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("BASEROOT"));
	Plant[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PLANT"));
	Plant[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Level1"));
	Plant[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Level2"));
	
	RootComponent = Root;
	Plant[0]->SetupAttachment(RootComponent);
	Plant[1]->SetupAttachment(RootComponent);
	Plant[2]->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_MESH0
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/vegetation01.vegetation01'"));
	if (SM_MESH0.Succeeded()) {
		Plant[0]->SetStaticMesh(SM_MESH0.Object);

	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_MESH1
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/vegetation02.vegetation02'"));
	if (SM_MESH1.Succeeded()) {
		Plant[1]->SetStaticMesh(SM_MESH1.Object);
		Plant[1]->SetVisibility(false);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_MESH2
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/vegetation03.vegetation03'"));
	if (SM_MESH2.Succeeded()) {
		Plant[2]->SetStaticMesh(SM_MESH2.Object);
		Plant[2]->SetVisibility(false);

	}

	//과일단계임 흠냐 소켓에다가 달아야하는데 쩝냐리
///	Plant[0]->GetSocketLocation()이거로 소켓네임써서 위치가져와서 거기다가 달면될듯


	WaterCount = 0;
	level = 0;
	IsDead = false;
	Days = 0;

}

// Called when the game starts or when spawned
void ATomato::BeginPlay()
{
	Super::BeginPlay();
	
	//타임핸들 가져오기

	TArray<AActor*> TimeOfDayHandler;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATimerHandler::StaticClass(),TimeOfDayHandler);

	if (TimeOfDayHandler.Num() != 0) {
		auto TimerHandler = Cast<ATimerHandler>(TimeOfDayHandler[0]);
		MyDelegate = TimerHandler->PlantDelegate.AddUObject(this, &ATomato::TimeChange);
	}
}

void ATomato::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

// Called every frame
void ATomato::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ATomato::TimeChange(int32 hours, int32 minutes)
{
	Hours = hours;
	Minute = minutes;
	//housr가 24되면 뭐 days를 올리고 level을 올리던가 어쩌구저쩌궇 ㅏ면될듯
	if (hours == 1) {
		level = 1;
		ChangePlant();

	}
	else if (hours == 2) {
		level = 2;
		ChangePlant();

	}
}


void ATomato::ChangePlant()
{
	Plant[0]->SetVisibility(false);
	Plant[1]->SetVisibility(false);
	Plant[2]->SetVisibility(false);


	Plant[level]->SetVisibility(true);
}

bool ATomato::IsDeadCheck()
{
	if (WaterCount == 0) {
		return true;
	}
	return false;
}

