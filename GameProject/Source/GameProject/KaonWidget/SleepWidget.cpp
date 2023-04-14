// Fill out your copyright notice in the Description page of Project Settings.


#include "SleepWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "../FindAppleGameMode.h"
#include "../FindApplePlayerController.h"
#include "../FindAppleCharacter.h"


void USleepWidget::NativeConstruct()
{
	Super::NativeConstruct();

	YesButton = Cast<UButton>(GetWidgetFromName(TEXT("Yes")));
	if (YesButton != nullptr) {
		YesButton->OnClicked.AddDynamic(this, &USleepWidget::YesChoice);
	}

	NoButton = Cast<UButton>(GetWidgetFromName(TEXT("No")));
	if (NoButton != nullptr) {
		NoButton->OnClicked.AddDynamic(this, &USleepWidget::NoChoice);
	}


	
}

void USleepWidget::YesChoice()
{
	UE_LOG(LogTemp, Warning, TEXT("YesChoice"));
	YesDelegate.ExecuteIfBound();
}

void USleepWidget::NoChoice()
{
	UE_LOG(LogTemp, Warning, TEXT("NOChoice"));
	NoDelegate.ExecuteIfBound();

}

