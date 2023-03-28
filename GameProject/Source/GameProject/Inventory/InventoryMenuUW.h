// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMenuUW.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UInventoryMenuUW : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UInventoryMenuUW(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* InventoryContentsWrap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FText InventoryName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInventoryUW* InventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* ItemDataTable;

	TArray<struct FInventoryTableRow*> InventoryData;
	
	/* Inventory Slot Class */
	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class UUserWidget> InventorySlotWidgetClass;
	UPROPERTY()
	class UInventorySlotUW* InventorySlotUIObject;
	/*UPROPERTY()
	bool bInventorySlotWidget = false;*/

	UFUNCTION()
	void Refresh();

	UFUNCTION()
	void ShowInventory(class UInventoryComponent* InventoryComp, FText Name);
};
