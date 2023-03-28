
// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotUW.h"
#include "InventoryUW.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "InventoryDataTable.h"	
#include "Engine/DataTable.h"
#include "Math/Color.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "InputCoreTypes.h"
#include "Input/Reply.h"
#include "ItemMenuTab.h"
#include "../FindAppleCharacter.h"

UInventorySlotUW::UInventorySlotUW(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
	}

	ConstructorHelpers::FClassFinder<UItemMenuTab>  ItemMenuWidgetFind(TEXT("WidgetBlueprint'/Game/Semin/UI/Inventory/UI/BP/WBP_ItemMenuTab.WBP_ItemMenuTab_C'"));
	if (ItemMenuWidgetFind.Succeeded())
	{
		ItemMenuTabClass = ItemMenuWidgetFind.Class;
	}
}

void UInventorySlotUW::NativeConstruct()
{
	Super::NativeConstruct();
	//ToolTipButton->OnClicked.AddDynamic(this, &UInventorySlotUW::ShowToolTip);
}

void UInventorySlotUW::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (Quantity < 1)
	{
		Quantity = 1;
	}
	/* int32 -> FText */
	FText TextQuantity = FText::FromString(FString::FromInt(Quantity));
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
					SlotImage->SetBrushFromTexture(InventoryRow.Thumbnail);
					SlotImage->SetBrushColor(FColor::White);
					Descript = InventoryRow.Descript;
					Name = InventoryRow.DisplayName;
					if (InventoryRow.ItemType == 1)
					{
						Eatable = true;
					}
				}
			}
		}
	}
}

FReply UInventorySlotUW::NativeOnMouseButtonDown(const FGeometry& MovieSceneBlends, const FPointerEvent& InMouseEvent)
{
	auto Reply = Super::NativeOnMouseButtonDown(MovieSceneBlends, InMouseEvent);
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		ShowToolTip();
		if (bIsViewMenu == true)
		{
			ItemMenuTabUIObject->RemoveFromParent();
			bIsViewMenu = false;
		}
	}

	return Reply;
}

void UInventorySlotUW::ShowToolTip()
{
	Widget->ShowToolTip(Name, Descript, ItemName, Eatable);

	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);
	MyCharacter->HideToolTip = false;
}
