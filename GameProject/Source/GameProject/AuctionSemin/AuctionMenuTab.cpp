// Fill out your copyright notice in the Description page of Project Settings.


#include "AuctionMenuTab.h"
#include "AuctionSlot.h"
#include "../Inventory/InventoryComponent.h"
#include "Components/WrapBox.h"
#include "../Inventory/InventoryDataTable.h"
#include "Kismet/GameplayStatics.h"
#include "../FindAppleCharacter.h"

UAuctionMenuTab::UAuctionMenuTab(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
	}

	ConstructorHelpers::FClassFinder<UAuctionSlot>  AuctionWidgetFind(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Auction/WBP_AuctionSlot.WBP_AuctionSlot_C'"));
	if (AuctionWidgetFind.Succeeded())
	{
		InventorySlotWidgetClass = AuctionWidgetFind.Class;
	}
}

void UAuctionMenuTab::NativeConstruct()
{
	Super::NativeConstruct();

	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	InventoryComponent = MyCharacter->InventoryComponent;
}

void UAuctionMenuTab::Refresh()
{
	InventoryContentsWrap->ClearChildren();

	if (InventoryComponent) {
		UE_LOG(LogTemp, Warning, TEXT("AuctionEnterWidget Refresh Inventory Component"));
		
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

							InventorySlotUIObject = CreateWidget<UAuctionSlot>(GetWorld(), InventorySlotWidgetClass);
							InventorySlotUIObject->Quantity = InventoryElement.Value;
							InventorySlotUIObject->ItemName = InventoryElement.Key;
							InventorySlotUIObject->AuctionEnterWidgetClass = AuctionEnterWidgetObject;
							if (AuctionEnterWidgetObject == NULL)
							{
								UE_LOG(LogTemp, Warning, TEXT("EnterWidget is NULL!!!!"));
							}
							InventoryContentsWrap->AddChildToWrapBox(InventorySlotUIObject);
						}
					}
				}
			}

		};
	}
}
