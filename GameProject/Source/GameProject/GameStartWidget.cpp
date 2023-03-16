// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStartWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Teleport/BlackScreenBegin.h"
#include "Teleport/BlackScreenEnd.h"

UGameStartWidget::UGameStartWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	ConstructorHelpers::FClassFinder<UBlackScreenBegin>  UBlackScreenBeginWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_BlackScreenBegin.WBP_BlackScreenBegin_C'"));
	if (UBlackScreenBeginWidget.Succeeded())
	{
		BlackScreenBeginClass = UBlackScreenBeginWidget.Class;
	}

	ConstructorHelpers::FClassFinder<UBlackScreenEnd>  UBlackScreenEndWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_BlackScreenEnd.WBP_BlackScreenEnd_C'"));
	if (UBlackScreenEndWidget.Succeeded())
	{
		BlackScreenEndClass = UBlackScreenEndWidget.Class;
	}
}

void UGameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &UGameStartWidget::GameStart);
}

void UGameStartWidget::GameStart()
{
	BlackScreenPopStart();

	FTimerHandle TimerHandle;
	float BlackScreenBeginTime = 0.8;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			UGameplayStatics::OpenLevel(this, TransferLevelName);

			BlackScreenBeginUIObject->RemoveFromParent();

			BlackScreenPopEnd();

		}), BlackScreenBeginTime, false);

	RemoveFromParent();
} 

void UGameStartWidget::CreateOptionWidget()
{
}

void UGameStartWidget::BlackScreenPopStart()
{
	BlackScreenBeginUIObject = CreateWidget<UBlackScreenBegin>(GetWorld(), BlackScreenBeginClass);
	BlackScreenBeginUIObject->AddToViewport();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PlayerController->SetShowMouseCursor(false);
}

void UGameStartWidget::BlackScreenPopEnd()
{
	BlackScreenEndUIObject = CreateWidget<UBlackScreenEnd>(GetWorld(), BlackScreenEndClass);
	BlackScreenEndUIObject->AddToViewport();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(false);
}

void UGameStartWidget::ChangeLevelAndDestroy()
{
}
