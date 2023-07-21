// Fill out your copyright notice in the Description page of Project Settings.


#include "TradeListWidget.h"
#include "TradePriceSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../FindAppleCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "../Inventory/InventoryComponent.h"
#include "../Inventory/InventoryDatatable.h"

#include "../MyGameInstance.h"

#include "../ClientSocket.h"


UTradeListWidget::UTradeListWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
		
	}
}

void UTradeListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BuyButton->OnClicked.AddDynamic(this, &UTradeListWidget::BuyButtonClick);

	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	InventoryComponent = MyCharacter->InventoryComponent;
}

void UTradeListWidget::BuyButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked Buy Button!!!"));

	static auto MyInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));


	static AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	static AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	if (InventoryComponent) {

		for (auto& InventoryElement : InventoryComponent->InventoryContent)
		{
			if (ItemDataTable != nullptr)
			{
				ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
				TArray<FName> RowNames = ItemDataTable->GetRowNames();

				if (InventoryElement.Key == FName("Gold") )
				{
				//	FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(InventoryElement.Key, InventoryElement.Key.ToString()));

					// 아이템 가격보다 많은 금을 가지고 있을 때만
					if (InventoryElement.Value > ItemPrice)
					{
						// 수량 개수 줄이는 곳 (Quantity = 구매할 때마다 감소하는 개수)
						Quantity -= 1;
						PriceSlot->QuantityText->SetText(FText::FromString(FString::FromInt(Quantity)));
						if (Quantity <= 0) {
							this->RemoveFromParent();
						}
						

					}
					else
					{
						return;
					}
				}
			}
		}

		// 한개씩 인벤토리에 증가
		MyCharacter->InventoryComponent->AddToInventory(ItemName, 1);
		// 가격만큼 인벤토리의 골드 감소
		MyCharacter->InventoryComponent->RemoveFromInventory(FName("Gold"), ItemPrice);
	}

	MyInstance->MySocket.SendRegistOrPurchasePacket(false, &ItemId);

}