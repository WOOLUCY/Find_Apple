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
	//이거 인스턴스에 저장하는거로 해야할듯.

	
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
	//여기서 날짜 변할때일 해주면됨

	if (Check) {
		++LiveDay;
		DeathCount = 0;//물주면 초기화해주기
		UE_LOG(LogTemp, Warning, TEXT("PlantWater "));

		//조건되면 레벨업해주기
		if (WaterCount > LevelUp) {
			//레벨업할때 하는일
			//1. watercount 초기화 - 그래야 다음 레벨에 갈 횟수 저장한다.
			WaterCount = 0;
			//2. Current메시 변경,레벨 올리기
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

