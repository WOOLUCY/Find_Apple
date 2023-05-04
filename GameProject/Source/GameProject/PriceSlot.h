// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PriceSlot.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UPriceSlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPriceSlot(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

public:
	UPROPERTY(EditAnywhere)
		class UTradeWidget* TradeWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* QuantityText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBorder* SlotImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBorder* CountImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		FName ItemName;
};
