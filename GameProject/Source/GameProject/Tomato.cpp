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

	//���ϴܰ��� ��� ���Ͽ��ٰ� �޾ƾ��ϴµ� ���ĸ�
///	Plant[0]->GetSocketLocation()�̰ŷ� ���ϳ��ӽἭ ��ġ�����ͼ� �ű�ٰ� �޸�ɵ�


	WaterCount = 0;
	level = 0;
	IsDead = false;
	Days = 0;

}

// Called when the game starts or when spawned
void ATomato::BeginPlay()
{
	Super::BeginPlay();
	
	//Ÿ���ڵ� ��������

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
	//housr�� 24�Ǹ� �� days�� �ø��� level�� �ø����� ��¼����¼�� ����ɵ�
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

