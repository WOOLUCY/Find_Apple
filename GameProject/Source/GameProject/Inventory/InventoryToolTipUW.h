// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryToolTipUW.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UInventoryToolTipUW : public UUserWidget
{
	GENERATED_BODY()

public:
	UInventoryToolTipUW(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DescriptText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* EatButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* DumpButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInventoryMenuUW* MenuWidget;

	TArray<struct FInventoryTableRow*> InventoryData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FText ItemName;

	UPROPERTY()
	FName NonDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FText Descript;

	UPROPERTY()
	bool Eatable = false;

	UFUNCTION()
	void SetText();

	UFUNCTION()
	void EattingItem();

	UFUNCTION()
	void RemoveItem();
};
