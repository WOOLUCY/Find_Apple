// Fill out your copyright notice in the Description page of Project Settings.


#include "AuctionSlot.h"
#include "AuctionEnterWidget.h"
#include "AuctionSelectSlot.h"
#include "../Inventory/InventoryDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/EditableTextBox.h"

UAuctionSlot::UAuctionSlot(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
	}

	/*ConstructorHelpers::FClassFinder<UAuctionEnterWidget>  AuctionEnterWidget(TEXT("WidgetBlueprint'/Game/Semin/UI/Inventory/UI/BP/WBP_ItemMenuTab.WBP_ItemMenuTab_C'"));
	if (AuctionEnterWidget.Succeeded())
	{
		AuctionEnterWidgetClass = AuctionEnterWidget.Class;
	}*/
}

void UAuctionSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

void UAuctionSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Quantity < 1)
	{
		Quantity = 0;
	}
	/* int32 -> FText */
	TextQuantity = FText::FromString(FString::FromInt(Quantity));
	QuantityText->SetText(TextQuantity);

	if (ItemDataTable != nullptr)
	{
		ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
		TArray<FName> RowNames = ItemDataTable->GetRowNames();

		for (FName RowName : RowNames)
		{
			FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

			if (RowName == ItemName)
			{
				if (InventoryRow.ItemType != 2) {
					// ItemType = 0은 섭취 불가능, 1 는 가능, 2 는인벤토리상 안 보이는 템
					Thumbnail = InventoryRow.Thumbnail;
					SlotImage->SetBrushFromTexture(Thumbnail);
					SlotImage->SetBrushColor(FColor::White);
					Descript = InventoryRow.Descript;
					Name = InventoryRow.DisplayName;
				}
			}
		}
	}
}

FReply UAuctionSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		if (AuctionEnterWidgetClass != NULL) 
		{
			AuctionEnterWidgetClass->SelectItemSlot->QuantityText->SetText(TextQuantity);
			AuctionEnterWidgetClass->SelectItemSlot->SlotImage->SetBrushFromTexture(Thumbnail);
			AuctionEnterWidgetClass->SelectItemName->SetText(Name);
			AuctionEnterWidgetClass->ItemName = Name;
			AuctionEnterWidgetClass->NonDisplayName = ItemName;

			FString StringName = *ItemName.ToString();
			if (StringName.Equals(FString(TEXT("apple")))) {
				AuctionEnterWidgetClass->ItmeType = APPLE;

			}
			else if (StringName.Equals(FString(TEXT("orange")))) {
				AuctionEnterWidgetClass->ItmeType = ORANGE;

			}
			else if (StringName.Equals(FString(TEXT("trunk")))) {
				AuctionEnterWidgetClass->ItmeType = TRUNK;

			}
			else if (StringName.Equals(FString(TEXT("rock")))) {
				AuctionEnterWidgetClass->ItmeType = ROCK;

			}
			else if (StringName.Equals(FString(TEXT("branch")))) {
				AuctionEnterWidgetClass->ItmeType = BRAHCN;

			}
			else if (StringName.Equals(FString(TEXT("Seed")))) {
				AuctionEnterWidgetClass->ItmeType = SEED;

			}
			else if (StringName.Equals(FString(TEXT("Iron")))) {
				AuctionEnterWidgetClass->ItmeType = IRON;

			}
			else if (StringName.Equals(FString(TEXT("Radish")))) {
				AuctionEnterWidgetClass->ItmeType = RADISH;

			}
			else if (StringName.Equals(FString(TEXT("Gold")))) {
				AuctionEnterWidgetClass->ItmeType = GOLD;

			}

		}
	}

	return Reply;
}

