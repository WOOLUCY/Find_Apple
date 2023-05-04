// Fill out your copyright notice in the Description page of Project Settings.


#include "Plant.h"
#include "Kismet/GameplayStatics.h"

#include "../FindAppleGameMode.h"

// Sets default values
APlant::APlant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void APlant::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Plant sPAnw!!"));

	float RandYaw = FMath::RandRange(-90.f, 90.f);

	SetActorRelativeRotation(FRotator(0.f, RandYaw, 0.f));



}

void APlant::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//�̰� �ν��Ͻ��� �����ϴ°ŷ� �ؾ��ҵ�.

	
}

// Called every frame
void APlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlant::PutWater()
{
	++WaterCount;
	DeathCount = 0;//���ָ� �ʱ�ȭ���ֱ�
	if (WaterCount >= LevelUp) {
		//�������Ҷ� �ϴ���
		//1. watercount �ʱ�ȭ - �׷��� ���� ������ �� Ƚ�� �����Ѵ�.
		WaterCount = 0;
		//2. Current�޽� ����,���� �ø���
		if (NowLevel < MaxLevel) {
			UE_LOG(LogTemp, Warning, TEXT("[NowLevel] : %d"), NowLevel);

			Current->SetStaticMesh(Meshs[NowLevel]);
			++NowLevel;
	

			
		}
		else {

			if (!IsFruit) {
				CanHarvest = true;
			}

		}
		
	}

	UE_LOG(LogTemp, Warning, TEXT("PlantWater Put ++"));
}

void APlant::DayChange()
{
	++DeathCount;
	if (DeathCount > MaxDeathDay) {
		UE_LOG(LogTemp, Warning, TEXT("PlantWater PDeath,,,,"));
		Destroy();

	}


}

void APlant::Harvest()
{
	if (CanHarvest){
		UE_LOG(LogTemp, Warning, TEXT("Call Harvest"));


	}
	else {

	}
	Destroy();

}

