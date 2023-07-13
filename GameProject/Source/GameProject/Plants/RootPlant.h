// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plant.h"
#include "RootPlant.generated.h"

/**
 * 
 */

enum ROOTTYPE { Radish=0, Carrot, Kohlrabi, Watermelon,TOTAL };

UCLASS()
class GAMEPROJECT_API ARootPlant : public APlant
{
	GENERATED_BODY()
public:
	ARootPlant();




	static int DemoCount;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};

int ARootPlant::DemoCount = Radish;