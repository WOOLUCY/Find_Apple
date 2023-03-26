// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingAllWidget.h"
#include "CraftingActor.h"
#include "CraftingItemsWidget.h"
#include "CraftingDataTable.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"
#include "../FindAppleCharacter.h"

UCraftingAllWidget::UCraftingAllWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

	/* Crafting Item Widget */
	static ConstructorHelpers::FClassFinder<UCraftingItemsWidget> CraftingItemWidgetFind(TEXT("WidgetBlueprint'/Game/Semin/UI/Crafting/WBP_CraftingItem.WBP_CraftingItem_C'"));
	if (CraftingItemWidgetFind.Succeeded())
	{
		CraftingItemWidgetClass = CraftingItemWidgetFind.Class;
	}

	/* Crafting Data Table */
	static ConstructorHelpers::FObjectFinder<UDataTable> CraftingDataTableObject(TEXT("/Script/Engine.DataTable'/Game/Semin/UI/Crafting/CraftingData.CraftingData'"));
	if (CraftingDataTableObject.Succeeded())
	{
		CraftingDataTable = CraftingDataTableObject.Object;
	}
}

void UCraftingAllWidget::NativeConstruct()
{
	Super::NativeConstruct();
	AXButton->OnClicked.AddDynamic(this, &UCraftingAllWidget::ClickedAXButton);
	PickButton->OnClicked.AddDynamic(this, &UCraftingAllWidget::ClickedPickButton);
	CloseButton->OnClicked.AddDynamic(this, &UCraftingAllWidget::ClickedCloseButton);

	if (CraftingDataTable != nullptr)
	{
		CraftingDataTable->GetAllRows<FCraftingTableRow>(TEXT("GetAllRows"), CraftingData);
		CraftingRowNames = CraftingDataTable->GetRowNames();
	}
}

void UCraftingAllWidget::CreateItemWidget(FName CraftingItemName)
{
	if (CraftingDataTable != nullptr)
	{
		for (FName RowName : CraftingRowNames)
		{
			if (RowName == CraftingItemName)
			{
				FCraftingTableRow Crafting = *(CraftingDataTable->FindRow<FCraftingTableRow>(RowName, RowName.ToString()));
				CraftingItemWidgetUIObject->AddToViewport();
				CraftingItemWidgetUIObject->SetCraftListWidget(RowName);
				CraftingItemWidgetUIObject->ItemName->SetText(Crafting.DisplayName);
				CraftingItemWidgetUIObject->ItemImage->SetBrushFromTexture(Crafting.CraftTexture);
				CraftingItemWidgetUIObject->ItemImage->SetBrushColor(FColor::White);
			}
		}
	}
}

/* ���� ��ư */
void UCraftingAllWidget::ClickedAXButton()
{
	CraftingItemWidgetUIObject = CreateWidget<UCraftingItemsWidget>(GetWorld(), CraftingItemWidgetClass);

	/* ��ư���� �ٲ��� �ϴ� �̸�, �����ͺ��̽��� �� �̸� */
	FName ButtonName = FName(TEXT("AX"));

	CreateItemWidget(ButtonName);

	RemoveFromParent();
}

/* ��� ��ư */
void UCraftingAllWidget::ClickedPickButton()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ClickedAXButton"));
	CraftingItemWidgetUIObject = CreateWidget<UCraftingItemsWidget>(GetWorld(), CraftingItemWidgetClass);

	/* ��ư���� �ٲ��� �ϴ� �̸�, �����ͺ��̽��� �� �̸� */
	FName ButtonName = FName(TEXT("Pick"));

	CreateItemWidget(ButtonName);

	RemoveFromParent();
}

void UCraftingAllWidget::ClickedCloseButton()
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

