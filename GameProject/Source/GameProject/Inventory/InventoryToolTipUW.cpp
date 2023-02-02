// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryToolTipUW.h"
#include "Components/TextBlock.h"

UInventoryToolTipUW::UInventoryToolTipUW(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void UInventoryToolTipUW::NativeConstruct()
{
	Super::NativeConstruct();
	ItemNameText->SetText(ItemName);
	DescriptText->SetText(Descript);
}

void UInventoryToolTipUW::SetText()
{
	ItemNameText->SetText(ItemName);
	DescriptText->SetText(Descript);
	UE_LOG(LogTemp, Warning, TEXT("SetText()asdw"));
}
