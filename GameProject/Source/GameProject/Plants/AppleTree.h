// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plant.h"
#include "AppleTree.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API AAppleTree : public APlant
{
	GENERATED_BODY()

public:
	AAppleTree();

protected:
	virtual void BeginPlay() override;
	virtual void PutWater() override;
	virtual bool Harvest() override;


private:

	
};
