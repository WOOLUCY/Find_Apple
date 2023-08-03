// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageListUI.h"
#include "Kismet/GameplayStatics.h"
#include "../FindAppleCharacter.h"
#include "MessageSlot.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"
#include "MessageHudWidget.h"
#include "MessageSendUI.h"

UMessageListUI::UMessageListUI(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	ConstructorHelpers::FClassFinder<UMessageSlot> MessageSlotWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Message/MessageSlotWidget.MessageSlotWidget_C'"));
	if (MessageSlotWidget.Succeeded())
	{
		MessageSlotWidgetClass = MessageSlotWidget.Class;
	}

	ConstructorHelpers::FClassFinder<UMessageSendUI> MessageSendWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Message/MessageSendWidget.MessageSendWidget_C'"));
	if (MessageSendWidget.Succeeded())
	{
		SendMessageWidgetClass = MessageSendWidget.Class;
	}
}

void UMessageListUI::NativeConstruct()
{
	Super::NativeConstruct();

	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	for (Message message : MyCharacter->MessageList) {
		MessageSlotWidgetUIObject = CreateWidget<UMessageSlot>(GetWorld(), MessageSlotWidgetClass);
		MessageSlotWidgetUIObject->TitleText->SetText(message.Title);
		MessageSlotWidgetUIObject->SenderText->SetText(message.Name);
		MessageList->AddChild(MessageSlotWidgetUIObject);
	}

	CloseButton->OnClicked.AddDynamic(this, &UMessageListUI::CloseButtonClick);
	SendButton->OnClicked.AddDynamic(this, &UMessageListUI::CreateSendMessageWidget);
}

void UMessageListUI::CloseButtonClick()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);

	MyCharacter->MessageWidget->ActiveMessageButton();

	RemoveFromParent();
}

void UMessageListUI::Refresh()
{
	MessageList->ClearChildren();

	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	// 가장 최근에 추가된(받은) 메시지가 가장 앞에 표시되도록 함 
	for (int i = MyCharacter->MessageList.Num() - 1; i >= 0; i--) {
		MessageSlotWidgetUIObject = CreateWidget<UMessageSlot>(GetWorld(), MessageSlotWidgetClass);
		MessageSlotWidgetUIObject->TitleText->SetText(MyCharacter->MessageList[i].Title);
		MessageSlotWidgetUIObject->SenderText->SetText(MyCharacter->MessageList[i].Name);
		MessageList->AddChild(MessageSlotWidgetUIObject);
	}
	/*for (Message message : MyCharacter->MessageList) {
		MessageSlotWidgetUIObject = CreateWidget<UMessageSlot>(GetWorld(), MessageSlotWidgetClass);
		MessageSlotWidgetUIObject->TitleText->SetText(message.Title);
		MessageSlotWidgetUIObject->SenderText->SetText(message.Name);
		MessageList->AddChild(MessageSlotWidgetUIObject);
	}*/
}

void UMessageListUI::CreateSendMessageWidget()
{
	SendMessageWidgetUIObject = CreateWidget<UMessageSendUI>(GetWorld(), SendMessageWidgetClass);
	SendMessageWidgetUIObject->AddToViewport();
	SendMessageWidgetUIObject->MessageListUIWidget = this;
	SendButton->SetIsEnabled(false);
}
