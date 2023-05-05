// Fill out your copyright notice in the Description page of Project Settings.


#include "TradeWidget.h"
#include "AuctionSemin/AuctionEnterWidget.h"
#include "AuctionSemin/AuctionMenuTab.h"
#include "AuctionSemin/AuctionSelectSlot.h"
#include "AuctionSemin/AuctionSlot.h"
#include "Components/Button.h"

void UTradeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TradeButton->OnClicked.AddDynamic(this, &UTradeWidget::TradeButtonClick);

	BuyButton01 = Cast<UButton>(GetWidgetFromName(TEXT("Buy01")));
	if (BuyButton01 != nullptr) {
		BuyButton01->OnClicked.AddDynamic(this, &UTradeWidget::BuyButton01Click);
	}
	BuyButton02 = Cast<UButton>(GetWidgetFromName(TEXT("Buy02")));
	if (BuyButton02 != nullptr) {
		BuyButton02->OnClicked.AddDynamic(this, &UTradeWidget::BuyButton01Click);
	}
	BuyButton03 = Cast<UButton>(GetWidgetFromName(TEXT("Buy03")));
	if (BuyButton03 != nullptr) {
		BuyButton03->OnClicked.AddDynamic(this, &UTradeWidget::BuyButton01Click);
	}
	BuyButton04 = Cast<UButton>(GetWidgetFromName(TEXT("Buy04")));
	if (BuyButton04 != nullptr) {
		BuyButton04->OnClicked.AddDynamic(this, &UTradeWidget::BuyButton01Click);
	}
}

void UTradeWidget::TradeButtonClick()
{
	if (AuctionWidgetUIObject != NULL) {
		AuctionWidgetUIObject->AddToViewport();
	}
}

void UTradeWidget::BuyButton01Click()
{
}

void UTradeWidget::BuyButton02Click()
{
}

void UTradeWidget::BuyButton03Click()
{
}

void UTradeWidget::BuyButton04Click()
{
}
