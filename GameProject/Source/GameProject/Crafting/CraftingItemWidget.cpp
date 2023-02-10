// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingItemWidget.h"
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


UCraftingItemWidget::UCraftingItemWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	/* Crafting All Widget */
	ConstructorHelpers::FClassFinder<UCraftingAllWidget>  CraftingAllWidgetFind(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Crafting/UI/WBP_CraftingAll.WBP_CraftingAll_C'"));
	if (CraftingAllWidgetFind.Succeeded())
	{
		CraftingAllWidgetClass = CraftingAllWidgetFind.Class;
	}

	/* Item Data Table */
	static ConstructorHelpers::FObjectFinder<UDataTable> InventoryDataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
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

	/* Crafting All Widget */
	ConstructorHelpers::FClassFinder<UCraftingListWidget>  CraftingListWidgetFind(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Crafting/UI/WBP_CraftingList.WBP_CraftingList_C'"));
	if (CraftingListWidgetFind.Succeeded())
	{
		CraftingListWidgetClass = CraftingListWidgetFind.Class;
	}
}

void UCraftingItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BackButton->OnClicked.AddDynamic(this, &UCraftingItemWidget::ClickedBackButton);
	CloseButton->OnClicked.AddDynamic(this, &UCraftingItemWidget::ClickedCloseButton);

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
}

void UCraftingItemWidget::SetCraftListWidget(FName CraftRowName)
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
				if (Crafting.branch != 0 /**/ ) {
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
}

void UCraftingItemWidget::ClickedBackButton()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ClickedAXButton"));
	CraftingAllWidgetUIObejct = CreateWidget<UCraftingAllWidget>(GetWorld(), CraftingAllWidgetClass);
	CraftingAllWidgetUIObejct->AddToViewport();
	RemoveFromParent();
}

void UCraftingItemWidget::ClickedCloseButton()
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

