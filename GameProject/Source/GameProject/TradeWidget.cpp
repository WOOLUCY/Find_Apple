// Fill out your copyright notice in the Description page of Project Settings.


#include "TradeWidget.h"
#include "Components/Button.h"

void UTradeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TradeButton = Cast<UButton>(GetWidgetFromName(TEXT("Trade")));
	if (TradeButton != nullptr) {
		TradeButton->OnClicked.AddDynamic(this, &UTradeWidget::TradeButtonClick);
	}
}

void UTradeWidget::TradeButtonClick()
{

}
