// Fill out your copyright notice in the Description page of Project Settings.


#include "AuctionEnterWidget.h"
#include "AuctionSlot.h"
#include "AuctionMenuTab.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

#include "../MyGameInstance.h"
#include "Internationalization/Text.h"

#include "../FindAppleCharacter.h"

UAuctionEnterWidget::UAuctionEnterWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	/*ConstructorHelpers::FClassFinder<UAuctionSlot>  AuctionSlotWidgetFind(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Auction/WBP_AuctionSlot.WBP_AuctionSlot_C'"));
	if (AuctionSlotWidgetFind.Succeeded())
	{
		SelectItemSlot = AuctionSlotWidgetFind.Class;
	}*/


	//InventoryAllItem->AuctionEnterWidgetObject = this;
}

void UAuctionEnterWidget::ClickedCloseButton()
{
	static auto MyInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	MyInstance->MySocket.PacketRecv();

	RemoveFromParent();

}

void UAuctionEnterWidget::ClickedEnterButton()
{
	//여기서 서버로 보내줘야함
	static auto MyInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	MyInstance->MySocket.SendTestSalePacket(ItmeType,ItemCount,ItemPrice);

	//인벤가지고 있는것도 줄여야함


}

void UAuctionEnterWidget::ChangedAmountTextBox(const FText& Text)
{
	if (!Text.IsNumeric()) {
		auto chopped = FText::FromString(Text.ToString().LeftChop(1));  // This gets rid of the last character in the text
		AmountTextBox->SetText(chopped);  // Set the text (you have to cache/SAssignNew the SEditableTextBox for this to work)
	}
	else 
	{
		ItemPrice = FCString::Atoi(*Text.ToString());
		TotalPrice = ItemPrice * ItemCount;

		AllAmount->SetText(FText::FromString(FString::FromInt(TotalPrice)));
	}
}

void UAuctionEnterWidget::ChangedCountTextBox(const FText& Text)
{
	if (!Text.IsNumeric()) {
		auto chopped = FText::FromString(Text.ToString().LeftChop(1));  // This gets rid of the last character in the text
		CountTextBox->SetText(chopped);  // Set the text (you have to cache/SAssignNew the SEditableTextBox for this to work)
	}
	else
	{
		ItemCount = FCString::Atoi(*Text.ToString());
		TotalPrice = ItemPrice * ItemCount;
		
		AllAmount->SetText(FText::FromString(FString::FromInt(TotalPrice)));
	}

}

void UAuctionEnterWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UAuctionEnterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked.AddDynamic(this, &UAuctionEnterWidget::ClickedCloseButton);
	EnterButton->OnClicked.AddDynamic(this, &UAuctionEnterWidget::ClickedEnterButton);
	AmountTextBox->OnTextChanged.AddDynamic(this, &UAuctionEnterWidget::ChangedAmountTextBox);
	CountTextBox->OnTextChanged.AddDynamic(this, &UAuctionEnterWidget::ChangedCountTextBox);

	InventoryAllItem->AuctionEnterWidgetObject = this;
	InventoryAllItem->Refresh();


}

