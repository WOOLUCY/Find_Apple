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


	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	InventoryComponent = MyCharacter->InventoryComponent;


	if (InventoryComponent) {
		for (auto& InventoryElement : InventoryComponent->InventoryContent)
		{
			if (ItemDataTable != nullptr)
			{
				ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
				TArray<FName> RowNames = ItemDataTable->GetRowNames();

				for (FName RowName : RowNames)
				{
					FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

					if (InventoryElement.Key == RowName)
					{
						if (InventoryRow.ItemType != 2) {
							TradeListWidgetUIObject = CreateWidget<UTradeListWidget>(GetWorld(), TradeListWidgetClass);
							TradeListWidgetUIObject->PriceSlot->SlotImage->SetBrushFromTexture(InventoryRow.Thumbnail);
							TradeListWidgetUIObject->PriceSlot->SlotImage->SetBrushColor(FColor::White);
							TradeListWidgetUIObject->PriceSlot->QuantityText->SetText(FText::FromString(FString::FromInt(InventoryElement.Value)));
							// InventoryElement.Value 는 그냥 개수(int) 변수 넣으면 되는 자리임

							// 밑의 코드는 price 받아서 넘겨야 함
							//TradeListWidgetUIObject->PriceSlot->SlotImage->SetBrushColor(nullptr);

							TradeList->AddChild(TradeListWidgetUIObject);
						}
					}
				}
			}
		}
	}
}

void UTradeWidget::TradeButtonClick()
{
	if (AuctionWidgetUIObject != NULL) {
		AuctionWidgetUIObject->AddToViewport();
		AuctionWidgetUIObject->TradeWidgetUIObject = this;
	}
}
