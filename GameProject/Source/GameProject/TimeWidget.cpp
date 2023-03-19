// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeWidget.h"
#include "Misc/DateTime.h"
#include "FindAppleGameMode.h"

#include "TimerHandler.h"
#include "Kismet/GameplayStatics.h"


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

			TArray<AActor*> TimeOfDayHandler;

			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATimerHandler::StaticClass(), TimeOfDayHandler);

			if (TimeOfDayHandler.Num() != 0) {
				auto TimerHandler = Cast<ATimerHandler>(TimeOfDayHandler[0]);
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

		TArray<AActor*> TimeOfDayHandler;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATimerHandler::StaticClass(), TimeOfDayHandler);

		if (TimeOfDayHandler.Num() != 0) {
			auto TimerHandler = Cast<ATimerHandler>(TimeOfDayHandler[0]);
			FString GameTimeString = TimerHandler->GetGameTime();

			return FText::FromString(TimerHandler->GetGameTime());

		}
		else {
			return FText::FromString("NULL");

		}



	}


	return FText::FromString("NULL");
}
