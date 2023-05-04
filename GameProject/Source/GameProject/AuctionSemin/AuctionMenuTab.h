// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuctionMenuTab.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UAuctionMenuTab : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UAuctionMenuTab(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* InventoryContentsWrap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FText InventoryName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAuctionEnterWidget* AuctionEnterWidgetObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* ItemDataTable;

	TArray<struct FInventoryTableRow*> InventoryData;
	
	/* Inventory Slot Class */
	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class UUserWidget> InventorySlotWidgetClass;
	UPROPERTY()
	class UAuctionSlot* InventorySlotUIObject;
	/*UPROPERTY()
	bool bInventorySlotWidget = false;*/

	UFUNCTION()
	void Refresh();
};
