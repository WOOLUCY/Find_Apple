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
	// ������ ��ư Ŭ���� �� �� �Լ��� ȣ��ȴ�.
	// ���⼭ SendID �� Title / DetailScript �� ������ �Ѱ��ָ� �ɵ���
	// ����� �׳� ������ �� ĳ���Ϳ��� �����ϵ��� ��

	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	Message Temp = { SendID, Title, DetailScript };
	MyCharacter->MessageList.Add(Temp);

	// �ؿ� Refresh �Լ��� ���� ���� �������� refresh ��, �ƹ�ư �� �����δ� ������ ��� ����
	MessageListUIWidget->Refresh();
	MessageListUIWidget->SendButton->SetIsEnabled(true);

	RemoveFromParent();
}