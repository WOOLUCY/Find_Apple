// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageSendUI.h"
#include "MessageListUI.h"
#include "../FindAppleCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/EditableTextBox.h"
#include "Components/MultiLineEditableTextBox.h"

UMessageSendUI::UMessageSendUI(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void UMessageSendUI::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked.AddDynamic(this, &UMessageSendUI::CloseButtonClick);
	SendButton->OnClicked.AddDynamic(this, &UMessageSendUI::SendButtonClick);
	NameTextBox->OnTextChanged.AddDynamic(this, &UMessageSendUI::ChangedNameTextBox);
	TitleTextBox->OnTextChanged.AddDynamic(this, &UMessageSendUI::ChangedTitleTextBox);
	DetailTextBox->OnTextChanged.AddDynamic(this, &UMessageSendUI::ChangedDetailTextBox);
}

void UMessageSendUI::CloseButtonClick()
{
	if (MessageListUIWidget) 
	{
		MessageListUIWidget->SendButton->SetIsEnabled(true);
	}
	RemoveFromParent();
}

void UMessageSendUI::ChangedNameTextBox(const FText& Text)
{
	SendID = Text;
}

void UMessageSendUI::ChangedDetailTextBox(const FText& Text)
{
	DetailScript = Text;
}

void UMessageSendUI::ChangedTitleTextBox(const FText& Text)
{
	Title = Text;
}

void UMessageSendUI::SendButtonClick()
{
	// 보내기 버튼 클릭할 때 이 함수가 호출된다.
	// 여기서 SendID 와 Title / DetailScript 를 서버로 넘겨주면 될듯함
	// 현재는 그냥 보내면 내 캐릭터에게 도착하도록 함

	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	Message Temp = { SendID, Title, DetailScript };
	MyCharacter->MessageList.Add(Temp);

	// 밑에 Refresh 함수는 나의 편지 보관함이 refresh 됨, 아무튼 이 밑으로는 서버와 상관 없음
	MessageListUIWidget->Refresh();
	MessageListUIWidget->SendButton->SetIsEnabled(true);

	RemoveFromParent();
}