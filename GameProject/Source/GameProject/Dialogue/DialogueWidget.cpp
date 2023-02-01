// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "Components/TextBlock.h"


UDialogueWidget::UDialogueWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

void UDialogueWidget::ChangeText(FText Name, FText Dialogue)
{
	DialogueTextBlock->SetText(Dialogue);
	NameTextBlock->SetText(Name);
}

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//DialogueTextBlock->SetText(FText::FromString("wqwqwqwqwqwq"));
}