// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryToolTipUW.h"
#include "InventoryDataTable.h"	
#include "InventoryMenuUW.h"
#include "DropedItem.h"
#include "Engine/DataTable.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "../FindAppleCharacter.h"
#include "InventoryComponent.h"

UInventoryToolTipUW::UInventoryToolTipUW(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
	}
}

void UInventoryToolTipUW::NativeConstruct()
{
	Super::NativeConstruct();
	EatButton->OnClicked.AddDynamic(this, &UInventoryToolTipUW::EattingItem);
	DumpButton->OnClicked.AddDynamic(this, &UInventoryToolTipUW::RemoveItem);
}

void UInventoryToolTipUW::SetText()
{
	this->SetVisibility(ESlateVisibility::Visible);

	ItemNameText->SetText(ItemName);
	DescriptText->SetText(Descript);
	UE_LOG(LogTemp, Warning, TEXT("SetText()asdw"));

	if (Eatable == false) {
		EatButton->SetVisibility(ESlateVisibility::Hidden);
	}

	else {
		EatButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void UInventoryToolTipUW::EattingItem()
{
	if (ItemDataTable != nullptr)
	{
		ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
		TArray<FName> RowNames = ItemDataTable->GetRowNames();

		for (FName RowName : RowNames)
		{
			FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

			if (RowName == NonDisplayName)
			{
				/* 캐릭터 체력 증가하도록 구현하기 */
				AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);
				MyCharacter->InventoryComponent->RemoveFromInventory(RowName, 1);
				MenuWidget->Refresh();
				this->SetVisibility(ESlateVisibility::Hidden);

				MyCharacter->SetCurHunger(MyCharacter->GetMaxHunger());
				MyCharacter->SetCurHealth(MyCharacter->GetCurHealth() + 20.f);
			}
		}
	}
}

void UInventoryToolTipUW::RemoveItem()
{
	if (ItemDataTable != nullptr)
	{
		ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
		TArray<FName> RowNames = ItemDataTable->GetRowNames();

		for (FName RowName : RowNames)
		{
			FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

			if (RowName == NonDisplayName)	/* Non-DisplayName = 표시용 이름이 아니라 행 이름 */
			{
				AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);
				MyCharacter->InventoryComponent->RemoveFromInventory(RowName, 1);
				MenuWidget->Refresh();
				this->SetVisibility(ESlateVisibility::Hidden);

				/* Actor Spawn */
				FActorSpawnParameters spawnParams;
				FRotator rotator;
				FVector spawnLocation = MyCharacter->GetActorLocation();
				//ADropedItem DropItem;
				//DropItem.ItemName = RowName;
				ADropedItem* DropedActor = GetWorld()->SpawnActor<ADropedItem>(ADropedItem::StaticClass(), spawnLocation, rotator, spawnParams);
				DropedActor->ItemFresh(RowName);

			}
		}
	}
}
