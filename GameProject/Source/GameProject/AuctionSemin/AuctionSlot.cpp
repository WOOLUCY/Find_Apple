// Fill out your copyright notice in the Description page of Project Settings.


#include "AuctionSlot.h"

UAuctionSlot::UAuctionSlot(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
	}


}

void UAuctionSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAuctionSlot::NativePreConstruct()
{
	Super::NativePreConstruct();
}

FReply UAuctionSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{

	}

	return Reply;
}
