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

	
protected:
	virtual void BeginPlay() override;
	virtual void PutWater() override;
	

private:

};
