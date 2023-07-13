// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plant.h"
#include "Tomato.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API ATomato : public APlant
{
	GENERATED_BODY()
public:
	ATomato();

	UStaticMesh* Fruit = nullptr;

	//int LiveDay = 0l;
	//int MaxDeathDay;
	//int DeathCount = 0;
	//int LevelUp = 1;
	//bool IsFruit = false;
	//TArray<UStaticMesh> Meshs;

	
protected:
	virtual void BeginPlay() override;
	virtual void PutWater() override;
	

private:
	//UPROPERTY(VisibleAnywhere, Category = Fruit)
	//UStaticMeshComponent* Fruit;


	
};
