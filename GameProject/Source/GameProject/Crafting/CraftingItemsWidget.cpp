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
	static ConstructorHelpers::FObjectFinder<UDataTable> CraftingDataTableObject(TEXT("/Script/Engine.DataTable'/Game/Semin/UI/Crafting/CraftingDataNew.CraftingDataNew'"));
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
		if (MyCharacter->InventoryComponent->InventoryContent.Find("apple")) {
			HaveAppleCnt = *MyCharacter->InventoryComponent->InventoryContent.Find("apple");
		}
		else
		{
			HaveAppleCnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("orange")) {
			HaveOrangeCnt = *MyCharacter->InventoryComponent->InventoryContent.Find("orange");
		}
		else
		{
			HaveOrangeCnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("branch")) {
			HaveBranchCnt = *MyCharacter->InventoryComponent->InventoryContent.Find("branch");
		}
		else
		{
			HaveBranchCnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("rock")) {
			HaveRockCnt = *MyCharacter->InventoryComponent->InventoryContent.Find("rock");
		}
		else
		{
			HaveRockCnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("trunk")) {
			HaveTrunkCnt = *MyCharacter->InventoryComponent->InventoryContent.Find("trunk");
		}
		else
		{
			HaveTrunkCnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("gold")) {
			HaveGoldCnt = *MyCharacter->InventoryComponent->InventoryContent.Find("gold");
		}
		else
		{
			HaveGoldCnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("iron")) {
			HaveIronCnt = *MyCharacter->InventoryComponent->InventoryContent.Find("iron");
		}
		else
		{
			HaveIronCnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("rubby")) {
			HaveRubbyCnt = *MyCharacter->InventoryComponent->InventoryContent.Find("rubby");
		}
		else
		{
			HaveRubbyCnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("sapphire")) {
			HaveSapphireCnt = *MyCharacter->InventoryComponent->InventoryContent.Find("sapphire");
		}
		else
		{
			HaveSapphireCnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("pick")) {
			HavePickCnt = *MyCharacter->InventoryComponent->InventoryContent.Find("pick");
		}
		else
		{
			HavePickCnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("pick1")) {
			HavePick1Cnt = *MyCharacter->InventoryComponent->InventoryContent.Find("pick1");
		}
		else
		{
			HavePick1Cnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("pick2")) {
			HavePick2Cnt = *MyCharacter->InventoryComponent->InventoryContent.Find("pick2");
		}
		else
		{
			HavePick2Cnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("pick3")) {
			HavePick3Cnt = *MyCharacter->InventoryComponent->InventoryContent.Find("pick3");
		}
		else
		{
			HavePick3Cnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("AX")) {
			HaveAXCnt = *MyCharacter->InventoryComponent->InventoryContent.Find("AX");
		}
		else
		{
			HaveAXCnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("AX1")) {
			HaveAX1Cnt = *MyCharacter->InventoryComponent->InventoryContent.Find("AX1");
		}
		else
		{
			HaveAX1Cnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("AX2")) {
			HaveAX3Cnt = *MyCharacter->InventoryComponent->InventoryContent.Find("AX2");
		}
		else
		{
			HaveAX2Cnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("AX3")) {
			HaveAX3Cnt = *MyCharacter->InventoryComponent->InventoryContent.Find("AX3");
		}
		else
		{
			HaveAX3Cnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("sword")) {
			HaveSwordCnt = *MyCharacter->InventoryComponent->InventoryContent.Find("sword");
		}
		else
		{
			HaveSwordCnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("sword1")) {
			HaveSword1Cnt = *MyCharacter->InventoryComponent->InventoryContent.Find("sword1");
		}
		else
		{
			HaveSword1Cnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("sword2")) {
			HaveSword2Cnt = *MyCharacter->InventoryComponent->InventoryContent.Find("sword2");
		}
		else
		{
			HaveSword2Cnt = 0;
		}
		if (MyCharacter->InventoryComponent->InventoryContent.Find("sword3")) {
			HaveSword3Cnt = *MyCharacter->InventoryComponent->InventoryContent.Find("sword3");
		}
		else
		{
			HaveSword3Cnt = 0;
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
				if (Crafting.gold != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("금"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.GoldTexture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.gold)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveGoldCnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.iron != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("철"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.IronTexture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.iron)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveIronCnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.rubby != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("루비"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.RubbyTexture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.rubby)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveRubbyCnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.sapphire != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("사파이어"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.SapphireTexture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.sapphire)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveSapphireCnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}

				// Pick
				if (Crafting.pick != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("나무 곡괭이"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.PickTexture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.pick)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HavePickCnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.pick1 != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("튼튼한 곡괭이"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.Pick1Texture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.pick1)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HavePick1Cnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.pick2 != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("금 곡괭이"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.Pick2Texture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.pick2)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HavePick2Cnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.pick3 != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("루비 곡괭이"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.Pick3Texture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.pick3)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HavePick3Cnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}

				// AX
				if (Crafting.AX != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("나무 도끼"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.AXTexture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.AX)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveAXCnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.AX1 != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("튼튼한 도끼"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.AX1Texture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.AX1)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveAX1Cnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.AX2 != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("금 도끼"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.AX2Texture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.AX2)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveAX2Cnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.AX3 != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("루비 도끼"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.AX3Texture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.AX3)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveAX3Cnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}


				// Sword
				if (Crafting.sword != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("나무 검"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.SwordTexture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.sword)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveSwordCnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.sword1 != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("튼튼한 검"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.Sword1Texture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.sword1)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveSword1Cnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.sword2 != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("금 검"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.Sword2Texture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.sword2)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveSword2Cnt)); /**/
					CraftingListUIObject->HaveCnt->SetText(HaveCnt);

					CraftingList->AddChild(CraftingListUIObject);
				}
				if (Crafting.sword3 != 0 /**/) {
					CraftingListUIObject = CreateWidget<UCraftingListWidget>(GetWorld(), CraftingListWidgetClass);
					FText NameDisplay = FText::FromName(FName(TEXT("루비 검"))); /**/
					CraftingListUIObject->ItemName->SetText(NameDisplay);

					CraftingListUIObject->ItemImage->SetBrushFromTexture(Crafting.Sword3Texture); /**/
					FText NeedCnt = FText::FromString(FString::FromInt(Crafting.sword3)); /**/
					CraftingListUIObject->NeedCnt->SetText(NeedCnt);

					FText HaveCnt = FText::FromString(FString::FromInt(HaveSword3Cnt)); /**/
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
					if (Crafting.gold != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("gold", Crafting.gold);
					}
					if (Crafting.iron != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("iron", Crafting.iron);
					}
					if (Crafting.rubby != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("rubby", Crafting.rubby);
					}
					if (Crafting.sapphire != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("sapphire", Crafting.sapphire);
					}
					if (Crafting.pick != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("pick", Crafting.pick);
					}
					if (Crafting.pick1 != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("pick1", Crafting.pick1);
					}
					if (Crafting.pick2 != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("pick2", Crafting.pick2);
					}
					if (Crafting.pick3 != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("pick3", Crafting.pick3);
					}
					if (Crafting.pick4 != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("pick4", Crafting.pick4);
					}
					if (Crafting.AX != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("AX", Crafting.AX);
					}
					if (Crafting.AX1 != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("AX1", Crafting.AX1);
					}
					if (Crafting.AX2 != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("AX2", Crafting.AX2);
					}
					if (Crafting.AX3 != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("AX3", Crafting.AX3);
					}
					if (Crafting.AX4 != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("AX4", Crafting.AX4);
					}
					if (Crafting.sword != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("sword", Crafting.sword);
					}
					if (Crafting.sword1 != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("sword1", Crafting.sword1);
					}
					if (Crafting.sword2 != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("sword2", Crafting.sword2);
					}
					if (Crafting.sword3 != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("sword3", Crafting.sword3);
					}
					if (Crafting.sword4 != 0) {
						MyCharacter->InventoryComponent->RemoveFromInventory("sword4", Crafting.sword4);
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
				if (Crafting.gold != 0) /**/ {
					if (HaveGoldCnt < Crafting.gold) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.iron != 0) /**/ {
					if (HaveIronCnt < Crafting.iron) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.rubby != 0) /**/ {
					if (HaveRubbyCnt < Crafting.rubby) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.sapphire != 0) /**/ {
					if (HaveSapphireCnt < Crafting.sapphire) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}


				if (Crafting.pick != 0) /**/ {
					if (HavePickCnt < Crafting.pick) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.pick1 != 0) /**/ {
					if (HavePick1Cnt < Crafting.pick1) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.pick2 != 0) /**/ {
					if (HavePick2Cnt < Crafting.pick2) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.pick3 != 0) /**/ {
					if (HavePick3Cnt < Crafting.pick3) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}

				if (Crafting.AX != 0) /**/ {
					if (HaveAXCnt < Crafting.AX) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.AX1 != 0) /**/ {
					if (HaveAX1Cnt < Crafting.AX1) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.AX2 != 0) /**/ {
					if (HaveAX2Cnt < Crafting.AX2) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.AX3 != 0) /**/ {
					if (HaveAX3Cnt < Crafting.AX3) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}

				if (Crafting.sword != 0) /**/ {
					if (HaveSwordCnt < Crafting.sword) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.sword1 != 0) /**/ {
					if (HaveSword1Cnt < Crafting.sword1) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.sword2 != 0) /**/ {
					if (HaveSword2Cnt < Crafting.sword2) /**/
					{
						CreateButton->SetIsEnabled(false);
						return;
					}
				}
				if (Crafting.sword3 != 0) /**/ {
					if (HaveSword3Cnt < Crafting.sword3) /**/
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

