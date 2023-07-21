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


	/* 판매하기 버튼 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* TradeButton;

	// Semin =
	UPROPERTY()
	TSubclassOf<class UUserWidget> AuctionWidgetClass;
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



public:
	/* Click Action */
	UFUNCTION()
	void TradeButtonClick();

	UFUNCTION()
	void Refrest();

};
