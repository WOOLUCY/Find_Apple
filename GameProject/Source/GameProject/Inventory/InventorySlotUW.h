// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../FindAppleInterface.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUW.h"
#include "InventorySlotUW.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UInventorySlotUW : public UUserWidget
{
	GENERATED_BODY()

protected:
	UInventorySlotUW(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* QuantityText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* SlotImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ToolTipButton;

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

	UFUNCTION()
	void ShowToolTip();
};
