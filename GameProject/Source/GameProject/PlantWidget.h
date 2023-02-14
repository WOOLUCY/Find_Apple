// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlantWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(AboutPlantDelegate)
UCLASS()
class GAMEPROJECT_API UPlantWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	AboutPlantDelegate SeedDelegate;
	AboutPlantDelegate WaterDelegate;
	AboutPlantDelegate HarvestDelegate;


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
	class UButton* SeedButton;

	UPROPERTY()
	class UButton* WaterButton;

	UPROPERTY()
	class UButton* HarvestButton;


};
