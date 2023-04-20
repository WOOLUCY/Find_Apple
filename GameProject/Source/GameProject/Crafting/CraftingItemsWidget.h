// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftingItemsWidget.generated.h"


/**
 *
 */
UCLASS()
class GAMEPROJECT_API UCraftingItemsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCraftingItemsWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* CreateButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UScrollBox* CraftingList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInventoryComponent* InventoryComponent;
	UFUNCTION()
	void SetCraftListWidget(FName CraftRowName);

private:
	/* Crafting All Widget */
	//UPROPERTY()
	//	TSubclassOf<class UUserWidget> CraftingAllWidgetClass;
	//UPROPERTY()
	//	class UCraftingAllWidget* CraftingAllWidgetUIObejct;

	/* Crafting List Widget Class */
	UPROPERTY()
	TSubclassOf<class UUserWidget> CraftingListWidgetClass;
	UPROPERTY()
	class UCraftingListWidget* CraftingListUIObject;

	UPROPERTY()
	class UDataTable* CraftingDataTable;
	TArray<struct FCraftingTableRow*> CraftingData;
	UPROPERTY()
	TArray<FName> CraftingRowNames;


	UPROPERTY()
	class UDataTable* ItemDataTable;
	TArray<struct FInventoryTableRow*> InventoryData;
	UPROPERTY()
	TArray<FName> ItemRowNames;

	/* need Change when I add item list */
	UPROPERTY()
	int32 HaveAppleCnt;
	UPROPERTY()
	int32 HaveOrangeCnt;
	UPROPERTY()
	int32 HaveBranchCnt;
	UPROPERTY()
	int32 HaveRockCnt;
	UPROPERTY()
	int32 HaveTrunkCnt;
	UPROPERTY()
	int32 HaveGoldCnt;
	UPROPERTY()
	int32 HaveIronCnt;
	UPROPERTY()
	int32 HaveRubbyCnt;
	UPROPERTY()
	int32 HaveSapphireCnt;
	
	// Tool
	UPROPERTY()
	int32 HavePickCnt;
	UPROPERTY()
	int32 HavePick1Cnt;
	UPROPERTY()
	int32 HavePick2Cnt;
	UPROPERTY()
	int32 HavePick3Cnt;
	// AX
	UPROPERTY()
	int32 HaveAXCnt;
	UPROPERTY()
	int32 HaveAX1Cnt;
	UPROPERTY()
	int32 HaveAX2Cnt;
	UPROPERTY()
	int32 HaveAX3Cnt;
	// Sword
	UPROPERTY()
	int32 HaveSwordCnt;
	UPROPERTY()
	int32 HaveSword1Cnt;
	UPROPERTY()
	int32 HaveSword2Cnt;
	UPROPERTY()
	int32 HaveSword3Cnt;

	//UPROPERTY()
	//int32 HasAppleCnt;

	/* Close */
	UFUNCTION()
	void ClickedCloseButton();
	UFUNCTION()
	void ClickedCreateButton();
	UFUNCTION()
	void CreateButtonSet(FName CraftRowName);
	UPROPERTY()
	FName CraftingName;
};
