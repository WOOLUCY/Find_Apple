// Fill out your copyright notice in the Description page of Project Settings.


#include "Plant.h"
#include "Kismet/GameplayStatics.h"

#include "../Inventory/InventoryComponent.h"
#include "../FindAppleCharacter.h"
#include "../FindAppleGameMode.h"

// Sets default values
APlant::APlant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CanHarvest = false;

}

// Called when the game starts or when spawned
void APlant::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Plant Spawn!!"));

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
		//	Meshs.
			Current->SetStaticMesh(Meshs[NowLevel]);
			++NowLevel;

			
			if (NowLevel == MaxLevel) {
				CanHarvest = true;
				UE_LOG(LogTemp, Warning, TEXT("PlantWater and CanHarvest"));

			}
		}
		
	}

}

void APlant::DayChange()
{
	++DeathCount;
	if (DeathCount > MaxDeathDay) {
		UE_LOG(LogTemp, Warning, TEXT("PlantWater PDeath,,,,"));
		//Destroy();

	}


}



bool APlant::Harvest()
{


	if (CanHarvest) {
		UE_LOG(LogTemp, Warning, TEXT("Call Harvest"));
	
		UE_LOG(LogTemp, Warning, TEXT("Plant In AddInvetory Function"));
		
		auto* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);
		if (MyCharacter != nullptr) {

			//MyCharacter->InventoryComponent
			MyCharacter->InventoryComponent->AddToInventory(ItemName, 1);

		}
		Destroy();
		return true;


	}
	else {
		return false;
	}

}

