// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantWidget.h"

void UPlantWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Seed = Cast<UButton>(GetWidgetFromName(TEXT("Seed")));
	if (Seed != nullptr) {
		Seed->OnClicked.AddDynamic(this, &UPlantWidget::PutSeed);
	}

	Water = Cast<UButton>(GetWidgetFromName(TEXT("Water")));
	if (Water != nullptr) {
		Water->OnClicked.AddDynamic(this, &UPlantWidget::PutWater);
	}

	Harvest = Cast<UButton>(GetWidgetFromName(TEXT("Harvest")));
	if (Harvest != nullptr) {
		Harvest->OnClicked.AddDynamic(this, &UPlantWidget::GetHarvest);
	}


}

void UPlantWidget::PutSeed()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PutSeed "));

}

void UPlantWidget::PutWater()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PutWater "));

}

void UPlantWidget::GetHarvest()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("GetHarvest "));

}
