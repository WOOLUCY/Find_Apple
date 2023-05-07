// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TradeWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UTradeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UTradeWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	/* �Ǹ��ϱ� ��ư */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* TradeButton;

	enum ITEM_TYPE { APPLE, ORANGE, FIREWOOD, ROCK, BRAHCN, SEED, GOLD, STEEL, RADISH };
	// Semin 
	UPROPERTY()
	class UAuctionEnterWidget* AuctionWidgetUIObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UScrollBox* TradeList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* ItemDataTable;

	UPROPERTY()
	FName SelectItemName;

	TArray<struct FInventoryTableRow*> InventoryData;

	UPROPERTY()
	TSubclassOf<class UUserWidget> TradeListWidgetClass;
	UPROPERTY()
	class UTradeListWidget* TradeListWidgetUIObject;

	struct SalesItem {
		int Item;
		int Num;
		int Price;
	};

	TArray<SalesItem> Items;

public:
	/* Click Action */
	UFUNCTION()
	void TradeButtonClick();
};