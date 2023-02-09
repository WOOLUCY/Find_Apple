// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PlantWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UPlantWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void PutSeed();

	UFUNCTION()
		void PutWater();


	UFUNCTION()
		void GetHarvest();


protected:
	UPROPERTY()
	class UButton* Seed;

	UPROPERTY()
	class UButton* Water;

	UPROPERTY()
	class UButton* Harvest;


};
