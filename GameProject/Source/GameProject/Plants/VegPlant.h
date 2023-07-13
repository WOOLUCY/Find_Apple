// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plant.h"
#include "VegPlant.generated.h"

/**
 * 
 */
enum VEGTYPE { Tomato = 0, Cucumber, Yellomelon };

UCLASS()
class GAMEPROJECT_API AVegPlant : public APlant
{
	GENERATED_BODY()

public:
	AVegPlant();


	static int DemoCount;
protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


private:
	
};
int AVegPlant::DemoCount = 0;