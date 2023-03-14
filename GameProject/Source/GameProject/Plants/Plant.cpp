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

	
	UE_LOG(LogTemp, Warning, TEXT("PlantWater Put ++"));
}

void APlant::DayChange()
{
	//���⼭ ��¥ ���Ҷ��� ���ָ��

	if (Check) {
		++LiveDay;
		DeathCount = 0;//���ָ� �ʱ�ȭ���ֱ�
		UE_LOG(LogTemp, Warning, TEXT("PlantWater "));

		//���ǵǸ� ���������ֱ�
		if (WaterCount > LevelUp) {
			//�������Ҷ� �ϴ���
			//1. watercount �ʱ�ȭ - �׷��� ���� ������ �� Ƚ�� �����Ѵ�.
			WaterCount = 0;
			//2. Current�޽� ����,���� �ø���
			if (NowLevel < MaxLevel) {
				Current->SetStaticMesh(Meshs[NowLevel]);
				++NowLevel;
			}			
		}
		Change= true;


	}
	else {
		++DeathCount;
		if (DeathCount > MaxDeathDay) {
			UE_LOG(LogTemp, Warning, TEXT("PlantWater PDeath,,,,"));
			Destroy();
			Change= false;

		}

	}
	Change= true;

	
}

void APlant::Harvest()
{
	if ((NowLevel == MaxLevel) && !IsFruit){
		UE_LOG(LogTemp, Warning, TEXT("Call Harvest"));


	}
	else {

	}
	Destroy();

}

