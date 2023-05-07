// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuctionEnterWidget.generated.h"

/**
 * 
 */
//PROTOCOL
//enum ITEM_TYPE { APPLE, ORANGE, FIREWOOD, PICK, AX, ROCK, BRAHCN, SEED, GOLD, STEEL, SWORD, RADISH };

UCLASS()
class GAMEPROJECT_API UAuctionEnterWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:

	UAuctionEnterWidget(const FObjectInitializer& objectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UAuctionMenuTab* InventoryAllItem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UAuctionSelectSlot* SelectItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FText DescriptText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AllAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SelectItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* CountTextBox = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* AmountTextBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* CloseButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* EnterButton;

	UPROPERTY(EditAnywhere)
	int ItemCount = 0;

	UPROPERTY()
	class UTradeWidget* TradeWidgetUIObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* ItemDataTable;

	TArray<struct FInventoryTableRow*> InventoryData;

	UPROPERTY()
	FName NonDisplayName;

	UPROPERTY(EditAnywhere)
	int ItemPrice = 0;

	UPROPERTY(EditAnywhere)
	int TotalPrice = 0;

	int ItmeType = -1;

	UFUNCTION()
	void ClickedCloseButton();
	UFUNCTION()
	void ClickedEnterButton();
	UFUNCTION()
	void ChangedAmountTextBox(const FText& Text);
	UFUNCTION()
	void ChangedCountTextBox(const FText& Text);
};
