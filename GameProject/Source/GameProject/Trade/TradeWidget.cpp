// Fill out your copyright notice in the Description page of Project Settings.


#include "TradeWidget.h"
#include "../AuctionSemin/AuctionEnterWidget.h"
#include "../AuctionSemin/AuctionMenuTab.h"
#include "../AuctionSemin/AuctionSelectSlot.h"
#include "../AuctionSemin/AuctionSlot.h"
#include "Components/Button.h"
#include "../ClientSocket.h"
#include "../MyGameInstance.h"
#include "TradeListWidget.h"

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

	static auto MyInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//Items = MyInstance->MySocket->items;
	//Items = MyInstance->MySocket.Items;

	for (auto& item : MyInstance->MySocket.Items ) {
		UE_LOG(LogTemp, Warning, TEXT("%d %d %d"), item.Item, item.Num, item.Price);
	}
}

void UTradeWidget::TradeButtonClick()
{
	if (AuctionWidgetUIObject != NULL) {
		AuctionWidgetUIObject->AddToViewport();
		AuctionWidgetUIObject->TradeWidgetUIObject = this;
	}
}
