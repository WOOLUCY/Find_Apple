// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plant.generated.h"

UCLASS()
class GAMEPROJECT_API APlant : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlant();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;


	int LiveDay = 0;	//살아있는날짜
	int WaterCount = 0; //물준날짜
	int MaxDeathDay=2;	//물안줘서 죽는날짜
	int DeathCount = 0; //물안준날짜
	int NowLevel = 0;	//현재성장단계의 식물
	int MaxLevel = 3;   //성장 최대단계
	int LevelUp = 1;	//성장하는 물줘야하는 횟수
	bool IsFruit = false;//열매있는지없는지
	bool CanHarvest = false; //수확시킬수있는지 없는지를 확인


	FName ItemName;


	TArray<UStaticMesh*> Meshs;

	UStaticMeshComponent* Current;

private:



	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PutWater();
	virtual bool Harvest();
	virtual void DayChange();

	

};
