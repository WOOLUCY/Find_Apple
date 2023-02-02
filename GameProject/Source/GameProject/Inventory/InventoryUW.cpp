// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUW.h"
#include "InventoryToolTipUW.h"
#include "InventoryMenuUW.h"
#include "Kismet/GameplayStatics.h"
#include "../FindAppleCharacter.h"

void UInventoryUW::NativePreConstruct()
{
	Super::NativePreConstruct();

	WBP_ToolTip->ItemName = ItemName;
	WBP_ToolTip->Descript = DescriptText;
	WBP_InventoryMenu->InventoryWidget = this;
}

void UInventoryUW::NativeConstruct()
{
	Super::NativeConstruct();

	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	WBP_InventoryMenu->ShowInventory(MyCharacter->InventoryComponent, FText());
	if (MyCharacter->HideToolTip == true)
	{
		WBP_ToolTip->SetVisibility(ESlateVisibility::Hidden);
	}
}

UInventoryUW::UInventoryUW(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}