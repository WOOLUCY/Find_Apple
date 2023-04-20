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

	/* Crafte Item Button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* AXButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* PickButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* AX1Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Pick1Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* AX2Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Pick2Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* AX3Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Pick3Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* AX4Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Pick4Button;
	// Sword Button
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* SwordButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Sword1Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Sword2Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Sword3Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Sword4Button;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* CloseButton;

	/* Crafting Item Widget */
	UPROPERTY()
	TSubclassOf<class UUserWidget> CraftingItemWidgetClass;
	UPROPERTY()
	class UCraftingItemsWidget* CraftingItemWidgetUIObject;

	UPROPERTY()
		class UDataTable* CraftingDataTable;
	TArray<struct FCraftingTableRow*> CraftingData;
	UPROPERTY()
		TArray<FName> CraftingRowNames;

	UPROPERTY()
		class UDataTable* ItemDataTable;
	TArray<struct FInventoryTableRow*> InventoryData;

	/* Button Click - Crafte Item Button */
	UFUNCTION()
		void ClickedAXButton();
	UFUNCTION()
		void ClickedPickButton();
	UFUNCTION()
		void ClickedAX1Button();
	UFUNCTION()
		void ClickedPick1Button();
	UFUNCTION()
		void ClickedAX2Button();
	UFUNCTION()
		void ClickedPick2Button();
	UFUNCTION()
		void ClickedAX3Button();
	UFUNCTION()
		void ClickedPick3Button();
	UFUNCTION()
		void ClickedAX4Button();
	UFUNCTION()
		void ClickedPick4Button();

	// Sword Button Func
	UFUNCTION()
	void ClickedSwordButton();
	UFUNCTION()
	void ClickedSword1Button();
	UFUNCTION()
	void ClickedSword2Button();
	UFUNCTION()
	void ClickedSword3Button();
	UFUNCTION()
	void ClickedSword4Button();


	/* Close */
	UFUNCTION()
		void ClickedCloseButton();
	UFUNCTION()
		void CreateItemWidget(FName CraftingItemName);
};
