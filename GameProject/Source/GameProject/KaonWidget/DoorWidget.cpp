// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "../FindAppleGameMode.h"
#include "../FindApplePlayerController.h"
#include "../FindAppleCharacter.h"

#include "Components/TextBlock.h"

void UDoorWidget::NativeConstruct()
{

	Super::NativeConstruct();

	YesButton = Cast<UButton>(GetWidgetFromName(TEXT("Yes")));
	if (YesButton != nullptr) {
		YesButton->OnClicked.AddDynamic(this, &UDoorWidget::YesChoice);
	}

	NoButton = Cast<UButton>(GetWidgetFromName(TEXT("No")));
	if (NoButton != nullptr) {
		NoButton->OnClicked.AddDynamic(this, &UDoorWidget::NoChoice);
	}

	TextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("Explanation")));

	if (TextBlock != nullptr) {
		TextBlock->SetText(FText::FromString(TEXT("들어가시겠습니까?")));
	}


}

void UDoorWidget::YesChoice()
{
	UE_LOG(LogTemp, Warning, TEXT("DoorYesChoice"));
	YesDelegate.ExecuteIfBound();

}

void UDoorWidget::NoChoice()
{
	UE_LOG(LogTemp, Warning, TEXT("DoorNoChoice"));
	NoDelegate.ExecuteIfBound();

}

