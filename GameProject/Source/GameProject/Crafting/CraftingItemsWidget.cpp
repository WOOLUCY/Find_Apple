// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingItemsWidget.h"
#include "CraftingAllWidget.h"
#include "CraftingListWidget.h"
#include "CraftingActor.h"
#include "CraftingDataTable.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"
#include "../FindAppleCharacter.h"
#include "../Inventory/InventoryComponent.h"
#include "../Inventory/InventoryDataTable.h"


UCraftingItemsWidget::UCraftingItemsWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	/* Item Data Table */
	static ConstructorHelpers::FObjectFinder<UDataTable> InventoryDataTable(TEXT("/Script/Engine.DataTable'/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable'"));
	if (InventoryDataTable.Succeeded())
	{
		ItemDataTable = InventoryDataTable.Object;
	}

	/* Crafting Data Table */
	static ConstructorHelpers::FObjectFinder<UDataTable> CraftingDataTableObject(TEXT("/Script/Engine.DataTable'/Game/Semin/UI/Crafting/CraftingData.CraftingData'"));
	if (CraftingDataTableObject.Succeeded())
	{
		CraftingDataTable = CraftingDataTableObject.Object;
	}

	/* Crafting List Widget */
	ConstructorHelpers::FClassFinder<UCraftingListWidget>  CraftingListWidgetFind(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Crafting/UI/WBP_CraftingList.WBP_CraftingList_C'"));
	if (CraftingListWidgetFind.Succeeded())
	{
		CraftingListWidgetClass = CraftingListWidgetFind.Class;
	}
}

void UCraftingItemsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CloseButton->OnClicked.AddDynamic(this, &UCraftingItemsWidget::ClickedCloseButton);
	CreateButton->OnClicked.AddDynamic(this, &UCraftingItemsWidget::ClickedCreateButton);

	if (CraftingDataTable != nullptr)
	{
		CraftingDataTable->GetAllRows<FCraftingTableRow>(TEXT("GetAllRows"), CraftingData);
		CraftingRowNames = CraftingDataTable->GetRowNames();
	}

	if (ItemDataTable != nullptr)
	{
		ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
		ItemRowNames = ItemDataTable->GetRowNames();
	}

}

void UCraftingItemsWidget::SetCraftListWidget(FName CraftRowName)
{
	CraftingName = CraftRowName;
	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	/* 아이템 추가할 때마다 고쳐야 함 */
	if (MyCharacter->InventoryComponent) {
		for (auto& InventoryElement : MyCharacter->InventoryComponent->InventoryContent)
		{
			/* 가지고 있는 사과의 개수 */
			if (InventoryElement.Key == FName(TEXT("apple")))
			{
				HaveAppleCnt = InventoryElement.Value;
			}
			/* 가지고 있는 오렌지의 개수 */
			if (InventoryElement.Key == FName(TEXT("orange")))
			{
				HaveOrangeCnt = InventoryElement.Value;
			}
			/* 가지고 있는 나뭇가지의 개수 */
			if (InventoryElement.Key == FName(TEXT("branch")))
			{
				HaveBranchCnt = InventoryElement.Value;
			}
			/* 가지고 있는 돌멩이의 개수 */
			if (InventoryElement.Key == FName(TEXT("rock")))
			{
				HaveRockCnt = InventoryElement.Value;
			}
			/* 가지고 있는 통나무의 개수 */
			if (InventoryElement.Key == FName(TEXT("trunk")))
			{
				HaveTrunkCnt = InventoryElement.Value;
			}
		}
	}

	CraftingList->ClearChildren();

	if (CraftingDataTable != nullptr)
	{
		for (FName RowName : CraftingRowNames)
		{
			/* 아이템 추가할 때마다 고쳐야 함 */
			if (RowName == CraftRowName)
			{
				FCraftingTableRow Crafting = *(CraftingDataTable->FindRow<FCraftingTableRow>(RowName, RowName.ToString()));

				if (Crafting.apple != 0) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("사과")));
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.AppleTexture);
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.apple));
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveAppleCnt));
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.orange != 0) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("오렌지")));
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.OrangeTexture);
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.orange));
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveOrangeCnt));
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.branch != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("나뭇가지"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.BranchTexture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.branch)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveBranchCnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.rock != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("돌멩이"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.RockTexture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.rock)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveRockCnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.trunk != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("통나무"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.TrunkTexture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.trunk)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveTrunkCnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
			}
		}
	}

	CreateButtonSet(CraftingName);
}

void UCraftingItemsWidget::ClickedCloseButton()
{
	TArray<AActor*> CraftableActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACraftingActor::StaticClass(), CraftableActors);

	AActor* ActorItr = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(ActorItr);

	for (AActor* Actor : CraftableActors)
	{
		ACraftingActor* CraftingActor = Cast<ACraftingActor>(Actor);

		if (CraftingActor != nullptr)
		{
			if (MyCharacter->IsOverlappingActor(Actor))
			{
				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				PlayerController->SetInputMode(FInputModeGameOnly());
				PlayerController->SetShowMouseCursor(false);
				CraftingActor->bIsWidgetValid = false;
			}
		}
	}

	RemoveFromParent();
}

void UCraftingItemsWidget::ClickedCreateButton()
{
	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	/* 아이템 추가할 때마다 고쳐야 함 */
	if (MyCharacter->InventoryComponent) {
		/* 만든 제작템을 인벤토리에 추가 */
		MyCharacter->InventoryComponent->AddToInventory(CraftingName, 1);
		//MyCharacter->InventoryComponent

		/* 제작한 뒤 재료 템들은 없어지도록 설정 */
		if (CraftingDataTable != nullptr)
		{
			for (FName RowName : CraftingRowNames)
			{
				/* 아이템 추가할 때마다 고쳐야 함 */
				if (RowName == CraftingName)
				{
					FCraftingTableRow Crafting = *(CraftingDataTable->FindRow<FCraftingTableRow>(RowName, RowName.ToString()));
					if (Crafting.apple != 0) {
						/* 캐릭터가 가진 수가 필요한 개수보다 적다면 button 비활성화 */
						MyCharacter->InventoryComponent->RemoveFromInventory("apple", Crafting.apple);
					}
					if (Crafting.orange != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("orange", Crafting.orange);
					}
					if (Crafting.branch != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("branch", Crafting.branch);
					}
					if (Crafting.rock != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("rock", Crafting.rock);
					}
					if (Crafting.trunk != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("trunk", Crafting.trunk);
					}
				}
			}
		}
	}
	/* 리스트 다시 세팅 */
	SetCraftListWidget(CraftingName);
}

void UCraftingItemsWidget::CreateButtonSet(FName CraftRowName)
{
	if (CraftingDataTable != nullptr)
	{
		for (FName RowName : CraftingRowNames)
		{
			/* 아이템 추가할 때마다 고쳐야 함 */
			if (RowName == CraftRowName)
			{
				FCraftingTableRow Crafting = *(CraftingDataTable->FindRow<FCraftingTableRow>(RowName, RowName.ToString()));
				if (Crafting.apple != 0) {
					/* 캐릭터가 가진 수가 필요한 개수보다 적다면 button 비활성화 */
					if (HaveAppleCnt < Crafting.apple)
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.orange != 0) {
					if (HaveOrangeCnt < Crafting.orange)
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.branch != 0) {
					if (HaveBranchCnt < Crafting.branch)
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.rock != 0) {
					if (HaveRockCnt < Crafting.rock)
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.trunk != 0) {
					if (HaveTrunkCnt < Crafting.trunk)
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
			}
		}
	}

	CreateButton->SetIsEnabled(true);
	return;
}

