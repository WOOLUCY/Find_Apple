// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingAllWidget.h"
#include "Components/Button.h"

UCraftingAllWidget::UCraftingAllWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void UCraftingAllWidget::NativeConstruct()
{
	Super::NativeConstruct();
	AXButton->OnClicked.AddDynamic(this, &UCraftingAllWidget::ClickedAXButton);
}

void UCraftingAllWidget::ClickedAXButton()
{
	UE_LOG(LogTemp, Warning, TEXT("ClickedAXButton"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ClickedAXButton"));
}
