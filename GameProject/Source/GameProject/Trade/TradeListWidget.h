// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TradeListWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UTradeListWidget : public UUserWidget
{
	GENERATED_BODY()

		
public:
	UTradeListWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTradePriceSlot* PriceSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Price;

	UPROPERTY()
	int32 Quantity;

	UPROPERTY()
	int32 ItemPrice;

	UPROPERTY()
	FName ItemName = "apple";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* BuyButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* ItemDataTable;

	TArray<struct FInventoryTableRow*> InventoryData;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UInventoryComponent* InventoryComponent;
	//UFUNCTION()
	//void SetCraftListWidget(FName CraftRowName);

	
	UFUNCTION()
	void BuyButtonClick();
};