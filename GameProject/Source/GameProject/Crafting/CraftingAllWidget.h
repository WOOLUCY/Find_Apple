// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftingAllWidget.generated.h"

/**
 *
 */
UCLASS()
class GAMEPROJECT_API UCraftingAllWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCraftingAllWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	/* ���� �߰��� ������ �߰��ؾ� �� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* AXButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* PickButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* CloseButton;

	/* Crafting Item Widget */
	UPROPERTY()
		TSubclassOf<class UUserWidget> CraftingItemWidgetClass;
	UPROPERTY()
		class UCraftingItemWidget* CraftingItemWidgetUIObject;

	UPROPERTY()
		class UDataTable* CraftingDataTable;
	TArray<struct FCraftingTableRow*> CraftingData;
	UPROPERTY()
		TArray<FName> CraftingRowNames;

	UPROPERTY()
		class UDataTable* ItemDataTable;
	TArray<struct FInventoryTableRow*> InventoryData;

	/* ���� �߰��� ������ �߰��ؾ� �� */
	UFUNCTION()
		void ClickedAXButton();
	UFUNCTION()
		void ClickedPickButton();
	/* Close */
	UFUNCTION()
		void ClickedCloseButton();
	UFUNCTION()
		void CreateItemWidget(FName CraftingItemName);
};
