// Fill out your copyright notice in the Description page of Project Settings.


#include "TradeWidget.h"
#include "TradePriceSlot.h"
#include "../AuctionSemin/AuctionEnterWidget.h"
#include "../AuctionSemin/AuctionMenuTab.h"
#include "../AuctionSemin/AuctionSelectSlot.h"
#include "../AuctionSemin/AuctionSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"

#include "../ClientSocket.h"
#include "../MyGameInstance.h"
#include "TradeListWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../Inventory/InventoryComponent.h"
#include "../Inventory/InventoryDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "../FindAppleCharacter.h"

UTradeWidget::UTradeWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	/* Trade List Widget */
	ConstructorHelpers::FClassFinder<UTradeListWidget> TradeListWidgetFind(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Woo/UI/TradeListWidget.TradeListWidget_C'"));
	if (TradeListWidgetFind.Succeeded())
	{
		TradeListWidgetClass = TradeListWidgetFind.Class;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
	}

	ConstructorHelpers::FClassFinder<UAuctionEnterWidget> EnterWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Auction/WBP_AuctionAll.WBP_AuctionAll_C'"));
	if (EnterWidget.Succeeded())
	{
		AuctionWidgetClass = EnterWidget.Class;
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

		if (item.Item == 0) {
			SelectItemName = FName("apple");
		}
		else if (item.Item == 1) {
			SelectItemName = FName("orange");
		}
		else if (item.Item == 2) {
			SelectItemName = FName("trunk");
		}
		else if (item.Item == 3) {
			SelectItemName = FName("rock");
		}
		else if (item.Item == 4) {
			SelectItemName = FName("branch");
		}
		else if (item.Item == 5) {
			SelectItemName = FName("seed");
		}
		else if (item.Item == 6) {
			SelectItemName = FName("gold");
		}
		else if (item.Item == 7) {
			SelectItemName = FName("steel");
		}
		else if (item.Item == 8) {
			SelectItemName = FName("radish");
		}

		if (ItemDataTable != nullptr)
		{
			ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
			TArray<FName> RowNames = ItemDataTable->GetRowNames();

			for (FName RowName : RowNames)
			{
				FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

				if (SelectItemName == RowName)
				{
					if (InventoryRow.ItemType != 2) {
						TradeListWidgetUIObject = CreateWidget<UTradeListWidget>(GetWorld(), TradeListWidgetClass);
						TradeListWidgetUIObject->PriceSlot->SlotImage->SetBrushFromTexture(InventoryRow.Thumbnail);
						TradeListWidgetUIObject->PriceSlot->SlotImage->SetBrushColor(FColor::White);
						TradeListWidgetUIObject->PriceSlot->QuantityText->SetText(FText::FromString(FString::FromInt(item.Num)));
						TradeListWidgetUIObject->Price->SetText(FText::FromString(FString::FromInt(item.Price)));

						TradeListWidgetUIObject->Quantity = item.Num;
						TradeListWidgetUIObject->ItemPrice = item.Price;
						TradeListWidgetUIObject->ItemName = RowName;

						TradeList->AddChild(TradeListWidgetUIObject);
					}
				}
			}
		}

	}
}

void UTradeWidget::TradeButtonClick()
{
	AuctionWidgetUIObject = CreateWidget<UAuctionEnterWidget>(GetWorld(), AuctionWidgetClass);
	AuctionWidgetUIObject->AddToViewport();
	AuctionWidgetUIObject->TradeWidgetUIObject = this;
}
