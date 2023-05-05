// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Inventory/InventoryUW.h"
#include "Blueprint/UserWidget.h"
#include "AuctionSelectSlot.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UAuctionSelectSlot : public UUserWidget
{
	GENERATED_BODY()
	
		
protected:
	UAuctionSelectSlot(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly)
	class UAuctionEnterWidget* AuctionEnterWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* QuantityText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TextQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* SlotImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* CountImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* EnterButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FName ItemName;

	UPROPERTY()
	FText Descript;

	UPROPERTY()
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryUW* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* ItemDataTable;

	TArray<struct FInventoryTableRow*> InventoryData;
};