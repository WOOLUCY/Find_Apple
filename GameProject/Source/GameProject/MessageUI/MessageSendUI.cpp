// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageSendUI.h"
#include "MessageListUI.h"
#include "Components/Button.h"
#include "Components/Border.h"

UMessageSendUI::UMessageSendUI(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void UMessageSendUI::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked.AddDynamic(this, &UMessageSendUI::CloseButtonClick);
}

void UMessageSendUI::CloseButtonClick()
{
	if (MessageListUIWidget) 
	{
		MessageListUIWidget->SendButton->SetIsEnabled(true);
	}
	RemoveFromParent();
}
