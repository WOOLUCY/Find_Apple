// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryMenuUW.h"
#include "InventoryComponent.h"
#include "InventorySlotUW.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WrapBox.h"

UInventoryMenuUW::UInventoryMenuUW(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
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
			InventorySlotUIObject = CreateWidget<UInventorySlotUW>(GetWorld(), InventorySlotWidgetClass);
			InventorySlotUIObject->Quantity = InventoryElement.Value;
			InventorySlotUIObject->ItemName = InventoryElement.Key;
			InventorySlotUIObject->Widget = InventoryWidget;
			InventoryContentsWrap->AddChildToWrapBox(InventorySlotUIObject);
		};
	}
}

void UInventoryMenuUW::ShowInventory(UInventoryComponent* InventoryComp, FText Name)
{
	InventoryComponent = InventoryComp;
	InventoryName = Name;
	Refresh();
}
