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
	DeathCount = 0;//물주면 초기화해주기
	if (WaterCount >= LevelUp) {
		//레벨업할때 하는일
		//1. watercount 초기화 - 그래야 다음 레벨에 갈 횟수 저장한다.
		WaterCount = 0;
		//2. Current메시 변경,레벨 올리기
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

