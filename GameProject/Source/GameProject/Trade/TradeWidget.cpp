// Fill out your copyright notice in the Description page of Project Settings.


#include "TradeWidget.h"
#include "../AuctionSemin/AuctionEnterWidget.h"
#include "../AuctionSemin/AuctionMenuTab.h"
#include "../AuctionSemin/AuctionSelectSlot.h"
#include "../AuctionSemin/AuctionSlot.h"
#include "Components/Button.h"
//#include "TradeListWidget.h"

UTradeWidget::UTradeWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	/* Trade List Widget */
	ConstructorHelpers::FClassFinder<UTradeListWidget> TradeListWidgetFind(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Woo/UI/TradeListWidget.TradeListWidget_C'"));
	if (TradeListWidgetFind.Succeeded())
	{
		TradeListWidgetClass = TradeListWidgetFind.Class;
	}

}

void UTradeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TradeButton->OnClicked.AddDynamic(this, &UTradeWidget::TradeButtonClick);
}

void UTradeWidget::TradeButtonClick()
{
	if (AuctionWidgetUIObject != NULL) {
		AuctionWidgetUIObject->AddToViewport();
		AuctionWidgetUIObject->TradeWidgetUIObject = this;
	}
}
