// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plant.h"
#include "RootPlant.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API ARootPlant : public APlant
{
	GENERATED_BODY()
public:
	ARootPlant();
	TArray<UStaticMesh*> Roots;


protected:
	virtual void BeginPlay() override;

	virtual void AddInventory();

};
