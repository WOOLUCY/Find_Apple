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
#include "Components/Border.h"


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
	for (auto& item : MyInstance->MySocket.Items) {

		switch (item.Value.Item)
		{
		case RADISH:
			SelectItemName = FName("Radish");
			kindofitem = RADISH;
			break;
		case CARROT:
			SelectItemName = FName("Carrot");
			kindofitem = CARROT;

			break;
		case KOHLRABI:
			SelectItemName = FName("Kohlrabi");
			kindofitem = KOHLRABI;

			break;
		case TOMATO:
			SelectItemName = FName("tomato");
			kindofitem = TOMATO;
			break;
		case CUCUMBER:
			SelectItemName = FName("cucumber");
			kindofitem = CUCUMBER;
			break;
		case YELLOMELON:
			SelectItemName = FName("yellomelon");
			kindofitem = YELLOMELON;
			break;
		case CACTUS:
			SelectItemName = FName("cactus");
			kindofitem = CACTUS;
			break;
		case APPLE:
			SelectItemName = FName("apple");
			kindofitem = APPLE;
			break;
		case GOLD:
			SelectItemName = FName("gold");
			kindofitem = GOLD;
			break;
		case IRON:
			SelectItemName = FName("iron");
			kindofitem = IRON;
			break;
		case RUBBY:
			SelectItemName = FName("rubby");
			kindofitem = RUBBY;
			break;
		case SAPPHIRE:
			SelectItemName = FName("sapphire");
			kindofitem = SAPPHIRE;
			break;
		case ROCK:
			SelectItemName = FName("rock");
			kindofitem = ROCK;
			break;
		case TRUNK:
			SelectItemName = FName("trunk");
			kindofitem = TRUNK;
			break;
		case BRANCH:
			SelectItemName = FName("branch");
			kindofitem = BRANCH;
			break;
		case SEED:
			SelectItemName = FName("seed");
			kindofitem = SEED;
			break;
		case FISH:
			SelectItemName = FName("fish");
			kindofitem = FISH;
			break;


		default:
			break;
		}



		if (ItemDataTable != nullptr)
		{
			ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
			TArray<FName> RowNames = ItemDataTable->GetRowNames();

			for (FName RowName : RowNames)
			{
				FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

				if (InventoryRow.KindOfItem == kindofitem)
				{
					if (InventoryRow.ItemType != 2) {
						TradeListWidgetUIObject = CreateWidget<UTradeListWidget>(GetWorld(), TradeListWidgetClass);
						TradeListWidgetUIObject->PriceSlot->SlotImage->SetBrushFromTexture(InventoryRow.Thumbnail);
						TradeListWidgetUIObject->PriceSlot->SlotImage->SetBrushColor(FColor::White);
						TradeListWidgetUIObject->PriceSlot->QuantityText->SetText(FText::FromString(FString::FromInt(item.Value.Num)));
						TradeListWidgetUIObject->Price->SetText(FText::FromString(FString::FromInt(item.Value.Price)));

						TradeListWidgetUIObject->Quantity = item.Value.Num;
						TradeListWidgetUIObject->ItemPrice = item.Value.Price;
						TradeListWidgetUIObject->ItemId = item.Value.RegisterId;
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
	AuctionWidgetUIObject->TradeWidgetUIObject = this;
	AuctionWidgetUIObject->AddToViewport();
}

void UTradeWidget::Refrest()
{
	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			TradeList->ClearChildren();

			static auto MyInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			for (auto& item : MyInstance->MySocket.Items) {



				switch (item.Value.Item)
				{
				case RADISH:
					SelectItemName = FName("Radish");
					break;
				case CARROT:
					SelectItemName = FName("Carrot");
					break;
				case KOHLRABI:
					SelectItemName = FName("Kohlrabi");
					break;
				case TOMATO:
					SelectItemName = FName("tomato");
					break;
				case CUCUMBER:
					SelectItemName = FName("cucumber");
					break;
				case YELLOMELON:
					SelectItemName = FName("yellomelon");
					break;
				case CACTUS:
					SelectItemName = FName("cactus");
					break;
				case APPLE:
					SelectItemName = FName("apple");
					break;
				case GOLD:
					SelectItemName = FName("gold");
					break;
				case IRON:
					SelectItemName = FName("iron");
					break;
				case RUBBY:
					SelectItemName = FName("rubby");
					break;
				case SAPPHIRE:
					SelectItemName = FName("sapphire");
					break;
				case ROCK:
					SelectItemName = FName("rock");
					break;
				case TRUNK:
					SelectItemName = FName("trunk");
					break;
				case BRANCH:
					SelectItemName = FName("branch");
					break;
				case SEED:
					SelectItemName = FName("seed");
					break;

				default:
					break;
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
								TradeListWidgetUIObject->PriceSlot->QuantityText->SetText(FText::FromString(FString::FromInt(item.Value.Num)));
								TradeListWidgetUIObject->Price->SetText(FText::FromString(FString::FromInt(item.Value.Price)));

								TradeListWidgetUIObject->Quantity = item.Value.Num;
								TradeListWidgetUIObject->ItemPrice = item.Value.Price;
								TradeListWidgetUIObject->ItemId = item.Value.RegisterId;

								TradeList->AddChild(TradeListWidgetUIObject);
							}
						}
					}
				}

			}
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), 1.f, false);




}
