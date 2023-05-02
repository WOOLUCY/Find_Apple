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
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* TradeButton;

public:
	/* Click Action */
	UFUNCTION()
		void TradeButtonClick();
};
