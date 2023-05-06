// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TradeListWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UTradeListWidget : public UUserWidget
{
	GENERATED_BODY()

		
public:
	UTradeListWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UTradeSlot* ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* BuyButton;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UInventoryComponent* InventoryComponent;
	//UFUNCTION()
	//void SetCraftListWidget(FName CraftRowName);
};