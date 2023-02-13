// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantWidget.h"
#include "Kismet/GamePlayStatics.h"
#include "FindAppleGameMode.h"
#include "Components/Button.h"



void UPlantWidget::NativeConstruct() 
{
	Super::NativeConstruct();

	SeedButton = Cast<UButton>(GetWidgetFromName(TEXT("Seed")));
	if (SeedButton != nullptr) {
		SeedButton->OnClicked.AddDynamic(this, &UPlantWidget::PutSeed);
	}

	WaterButton = Cast<UButton>(GetWidgetFromName(TEXT("Water")));
	if (WaterButton != nullptr) {
		WaterButton->OnClicked.AddDynamic(this, &UPlantWidget::PutWater);
	}

	HarvestButton = Cast<UButton>(GetWidgetFromName(TEXT("Harvest")));
	if (HarvestButton != nullptr) {
		HarvestButton->OnClicked.AddDynamic(this, &UPlantWidget::GetHarvest);
	}



}

void UPlantWidget::PutSeed()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PutSeed "));

	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr) {
		AFindAppleGameMode* MyMode = Cast<AFindAppleGameMode>(UGameplayStatics::GetGameMode(TheWorld));
		if (MyMode != nullptr) {
			MyMode->SeedDelegate.Broadcast();
		}
	}
}

void UPlantWidget::PutWater()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PutWater "));

	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr) {
		AFindAppleGameMode* MyMode = Cast<AFindAppleGameMode>(UGameplayStatics::GetGameMode(TheWorld));
		if (MyMode != nullptr) {
			MyMode->WaterDelegate.Broadcast();

		}
	}

}

void UPlantWidget::GetHarvest()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("GetHarvest "));
	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr) {
		AFindAppleGameMode* MyMode = Cast<AFindAppleGameMode>(UGameplayStatics::GetGameMode(TheWorld));
		if (MyMode != nullptr) {
			MyMode->HarvestDelegate.Broadcast();
		}
	}

}
