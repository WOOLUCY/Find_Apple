// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantWidget.h"
#include "Kismet/GamePlayStatics.h"
#include "../FindAppleGameMode.h"
#include "Components/Button.h"
#include "../Inventory/InventoryDataTable.h"
#include "../Inventory/InventoryComponent.h"
#include "../FindAppleCharacter.h"
#include "Kismet/GameplayStatics.h"


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
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PutSeed "));

	if (ItemDataTable != nullptr)
	{
		ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
		TArray<FName> RowNames = ItemDataTable->GetRowNames();

		for (FName RowName : RowNames)
		{
			FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

			if (RowName == FName("Seed"))
			{
				AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);
				MyCharacter->InventoryComponent->RemoveFromInventory(RowName, 1);
			}
		}
	}

	SeedDelegate.ExecuteIfBound();
	//SeedDelegate.Broadcast();
}

void UPlantWidget::PutWater()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PutWater "));

	WaterDelegate.ExecuteIfBound();
	//WaterDelegate.Broadcast();
}

void UPlantWidget::GetHarvest()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("GetHarvest "));
	HarvestDelegate.ExecuteIfBound();
	//HarvestDelegate.Broadcast();
}
