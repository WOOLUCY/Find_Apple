// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryMenuUW.h"
#include "InventoryComponent.h"
#include "InventorySlotUW.h"
#include "InventoryDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WrapBox.h"

UInventoryMenuUW::UInventoryMenuUW(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
	}

	/* Inventory Widget */
	ConstructorHelpers::FClassFinder<UInventorySlotUW>  InventoryWidgetFind(TEXT("WidgetBlueprint'/Game/Semin/UI/Inventory/UI/BP/WBP_InventoryMenuSlotCPP.WBP_InventoryMenuSlotCPP_C'"));
	if (InventoryWidgetFind.Succeeded())
	{
		InventorySlotWidgetClass = InventoryWidgetFind.Class;
	}
}

void UInventoryMenuUW::NativeConstruct()
{
	Super::NativeConstruct();

}

void UInventoryMenuUW::Refresh()
{
	InventoryContentsWrap->ClearChildren();
	if (InventoryComponent) {
		for (auto& InventoryElement : InventoryComponent->InventoryContent)
		{	
			UE_LOG(LogTemp, Warning, TEXT("Refresh in Inventory"))
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

							InventorySlotUIObject = CreateWidget<UInventorySlotUW>(GetWorld(), InventorySlotWidgetClass);
							InventorySlotUIObject->Quantity = InventoryElement.Value;
							InventorySlotUIObject->ItemName = InventoryElement.Key;
							InventorySlotUIObject->Widget = InventoryWidget;
							InventoryContentsWrap->AddChildToWrapBox(InventorySlotUIObject);
						}
					}
				}
			}

		};
	}
}

void UInventoryMenuUW::ShowInventory(UInventoryComponent* InventoryComp, FText Name)
{
	InventoryComponent = InventoryComp;
	InventoryName = Name;
	Refresh();
}
