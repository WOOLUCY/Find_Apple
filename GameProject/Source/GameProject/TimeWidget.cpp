// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeWidget.h"
#include "Misc/DateTime.h"
#include "FindAppleGameMode.h"
#include "Components/TextBlock.h"

UTimeWidget::UTimeWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void UTimeWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

bool UTimeWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success)
	{
		return false;
	}

	if (TimeText)
	{
		UWorld* World = GetWorld();

		if (World != nullptr)
		{
			AFindAppleGameMode* FindAppleGameMode = Cast<AFindAppleGameMode>(World->GetAuthGameMode());

			if (FindAppleGameMode)
			{
				TimeText->SetText(FText::FromString("Game Mode Set"));

				TimeText->TextDelegate.BindUFunction(this, "SetTimeText");
			}
		}
	}

	return false;
}

FText UTimeWidget::SetTimeText()
{
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		AFindAppleGameMode* FindAppleGameMode = Cast<AFindAppleGameMode>(World->GetAuthGameMode());

		if (FindAppleGameMode)
		{
			FString GameTimeString = FindAppleGameMode->GetGameTime();

			return FText::FromString(FindAppleGameMode->GetGameTime());
		}
		else 
		{
			return FText::FromString("NULL");
		}
	}

	return FText::FromString("NULL");
}
