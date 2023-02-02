
// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotUW.h"
#include "InventoryUW.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "InventoryDataTable.h"	
#include "Engine/DataTable.h"
#include "Math/Color.h"
#include "Kismet/GameplayStatics.h"
#include "../FindAppleCharacter.h"

UInventorySlotUW::UInventorySlotUW(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
	}
}

void UInventorySlotUW::NativeConstruct()
{
	Super::NativeConstruct();
	ToolTipButton->OnClicked.AddDynamic(this, &UInventorySlotUW::ShowToolTip);
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
				SlotImage->SetBrushFromTexture(InventoryRow.Thumbnail);
				SlotImage->SetBrushColor(FColor::White);
				Descript = InventoryRow.Descript;
				Name = InventoryRow.DisplayName;
				UE_LOG(LogTemp, Warning, TEXT("Apple"));
			}
		}
	}
}

void UInventorySlotUW::ShowToolTip()
{
	Widget->ShowToolTip(Name, Descript);

	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);
	MyCharacter->HideToolTip = false;

	TArray<AActor*> TalkableActor;

	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UFindAppleInterface::StaticClass(), TalkableActor);

}
