// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageHudWidget.h"
#include "Components/Button.h"
#include "MessageListUI.h"
#include "Kismet/GameplayStatics.h"

UMessageHudWidget::UMessageHudWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	ConstructorHelpers::FClassFinder<UMessageListUI> MessageObject(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Message/MessageListWidget.MessageListWidget_C'"));
	if (MessageObject.Succeeded())
	{
		MessageListWidgetClass = MessageObject.Class;
	}
}

void UMessageHudWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	MessageButton->OnClicked.AddDynamic(this, &UMessageHudWidget::MessageButtonClick);
}

void UMessageHudWidget::MessageButtonClick()
{
	MessageListWidgetUIObject = CreateWidget<UMessageListUI>(GetWorld(), MessageListWidgetClass);
	MessageListWidgetUIObject->AddToViewport();


	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PlayerController->SetInputMode(FInputModeGameAndUI());
	PlayerController->SetShowMouseCursor(true);

	DisableMessageButton();
}

void UMessageHudWidget::ActiveMessageButton()
{
	MessageButton->SetIsEnabled(true);
}

void UMessageHudWidget::DisableMessageButton()
{
	MessageButton->SetIsEnabled(false);
}
