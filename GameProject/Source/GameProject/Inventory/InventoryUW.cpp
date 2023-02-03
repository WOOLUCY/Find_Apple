// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUW.h"
#include "InventoryToolTipUW.h"
#include "InventoryMenuUW.h"
#include "Kismet/GameplayStatics.h"
#include "../FindAppleCharacter.h"

void UInventoryUW::NativePreConstruct()
{
	Super::NativePreConstruct();

	WBP_ToolTipCPP->ItemName = ItemName;
	WBP_ToolTipCPP->Descript = DescriptText;
	WBP_InventoryMenu->InventoryWidget = this;
}

void UInventoryUW::NativeConstruct()
{
	Super::NativeConstruct();

	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	WBP_InventoryMenu->ShowInventory(MyCharacter->InventoryComponent, FText());
	WBP_ToolTipCPP->SetVisibility(ESlateVisibility::Hidden);
}

UInventoryUW::UInventoryUW(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

void UInventoryUW::ShowToolTip(FText NameTextIn, FText DescriptTextIn, FName NonDisplayName, bool Eatable)
{
	UE_LOG(LogTemp, Warning, TEXT("ShowToolTip"));
	WBP_ToolTipCPP->ItemName = NameTextIn;
	WBP_ToolTipCPP->Descript = DescriptTextIn;
	WBP_ToolTipCPP->Eatable = Eatable;
	WBP_ToolTipCPP->NonDisplayName = NonDisplayName;
	WBP_ToolTipCPP->MenuWidget = WBP_InventoryMenu;
	WBP_ToolTipCPP->SetText();
	WBP_ToolTipCPP->SetVisibility(ESlateVisibility::Visible);
}
