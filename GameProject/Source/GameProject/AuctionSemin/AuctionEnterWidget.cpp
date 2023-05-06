// Fill out your copyright notice in the Description page of Project Settings.


#include "AuctionEnterWidget.h"
#include "AuctionSlot.h"
#include "AuctionMenuTab.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

#include "../MyGameInstance.h"
#include "Internationalization/Text.h"

#include "../FindAppleCharacter.h"
#include "../Trade/TradeWidget.h"
#include "../Inventory/InventoryComponent.h"
#include "../Inventory/InventoryDataTable.h"

UAuctionEnterWidget::UAuctionEnterWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	/*ConstructorHelpers::FClassFinder<UAuctionSlot>  AuctionSlotWidgetFind(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Auction/WBP_AuctionSlot.WBP_AuctionSlot_C'"));
	if (AuctionSlotWidgetFind.Succeeded())
	{
		SelectItemSlot = AuctionSlotWidgetFind.Class;
	}*/

	//InventoryAllItem->AuctionEnterWidgetObject = this;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
	}
}

void UAuctionEnterWidget::ClickedCloseButton()
{
	static auto MyInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	MyInstance->MySocket.PacketRecv();

	RemoveFromParent();

}

void UAuctionEnterWidget::ClickedEnterButton()
{
	//여기서 서버로 보내줘야함

	//인벤가지고 있는것도 줄여야함
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
				
				// 인벤토리 내의 개수가 ItemCount보다 더 많거나 같을 때만 
				if (*MyCharacter->InventoryComponent->InventoryContent.Find(RowName) >= ItemCount)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Out"));
					MyCharacter->InventoryComponent->RemoveFromInventory(RowName, ItemCount);
					
					// 보낼 수 있는 개수일 때만 서버한테 보냄
					static auto MyInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
					//MyInstance->MySocket.SendTestSalePacket(ItmeType, ItemCount, ItemPrice);
				}
			}
		}
	}

}

void UAuctionEnterWidget::ChangedAmountTextBox(const FText& Text)
{
	if (!Text.IsNumeric()) {
		auto chopped = FText::FromString(Text.ToString().LeftChop(1));  // This gets rid of the last character in the text
		AmountTextBox->SetText(chopped);  // Set the text (you have to cache/SAssignNew the SEditableTextBox for this to work)
	}
	else 
	{
		ItemPrice = FCString::Atoi(*Text.ToString());
		TotalPrice = ItemPrice * ItemCount;

		AllAmount->SetText(FText::FromString(FString::FromInt(TotalPrice)));
	}
}

void UAuctionEnterWidget::ChangedCountTextBox(const FText& Text)
{
	if (!Text.IsNumeric()) {
		auto chopped = FText::FromString(Text.ToString().LeftChop(1));  // This gets rid of the last character in the text
		CountTextBox->SetText(chopped);  // Set the text (you have to cache/SAssignNew the SEditableTextBox for this to work)
	}
	else
	{
		ItemCount = FCString::Atoi(*Text.ToString());
		TotalPrice = ItemPrice * ItemCount;
		
		AllAmount->SetText(FText::FromString(FString::FromInt(TotalPrice)));
	}

}

void UAuctionEnterWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UAuctionEnterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked.AddDynamic(this, &UAuctionEnterWidget::ClickedCloseButton);
	EnterButton->OnClicked.AddDynamic(this, &UAuctionEnterWidget::ClickedEnterButton);
	AmountTextBox->OnTextChanged.AddDynamic(this, &UAuctionEnterWidget::ChangedAmountTextBox);
	CountTextBox->OnTextChanged.AddDynamic(this, &UAuctionEnterWidget::ChangedCountTextBox);

	InventoryAllItem->AuctionEnterWidgetObject = this;
	InventoryAllItem->Refresh();


}

