// Fill out your copyright notice in the Description page of Project Settings.


#include "AuctionSelectSlot.h"
#include "AuctionEnterWidget.h"
#include "../Inventory/InventoryDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

UAuctionSelectSlot::UAuctionSelectSlot(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
	}

}

void UAuctionSelectSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAuctionSelectSlot::NativePreConstruct()
{
	Super::NativePreConstruct();
}