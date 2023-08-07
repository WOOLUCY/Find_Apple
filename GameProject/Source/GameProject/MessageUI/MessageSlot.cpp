// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MessageInfoUI.h"
#include "MessageListUI.h"

UMessageSlot::UMessageSlot(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void UMessageSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SlotButton->OnClicked.AddDynamic(this, &UMessageSlot::SlotButtonClick);
}

void UMessageSlot::SlotButtonClick()
{
	if (MessageListUIWidget) {
		MessageListUIWidget->SetInfoUIWidget(SenderText->GetText(), TitleText->GetText(), DetailText->GetText());
	}
}
