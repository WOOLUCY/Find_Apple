// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageInfoUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../FindAppleCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MessageHudWidget.h"
#include "MessageListUI.h"


UMessageInfoUI::UMessageInfoUI(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

void UMessageInfoUI::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked.AddDynamic(this, &UMessageInfoUI::CloseButtonClick);
}

void UMessageInfoUI::CloseButtonClick()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(true);

	MyCharacter->MessageWidget->ActiveMessageButton();
	
	MessageListUIWidget->MessageInfoOpened = false;
	RemoveFromParent();
}
