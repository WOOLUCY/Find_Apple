// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"

#include "FindAppleCharacter.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "StartAndOption/GameOptionWidget.h"

UPauseWidget::UPauseWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	/* Option Widget */
	ConstructorHelpers::FClassFinder<UGameOptionWidget>  gameOptionWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/GameStart/WBP_OptionWidget.WBP_OptionWidget_C'"));
	if (gameOptionWidget.Succeeded())
	{
		OptionWidgetClass = gameOptionWidget.Class;
	}
}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ExitButton->OnClicked.AddDynamic(this, &UPauseWidget::ExitButtonClick);
	ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::ResumeButtonClick);
	OptionButton->OnClicked.AddDynamic(this, &UPauseWidget::OptionButtononClick);
}

void UPauseWidget::ResumeButtonClick()
{
	AFindAppleCharacter* MyChar = Cast<AFindAppleCharacter>(GetOwningPlayerPawn());
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	MyChar->PauseUIObject->RemoveFromParent();
	PlayerController->SetPause(!MyChar->bPauseWidget);
	MyChar->bPauseWidget = false;
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
}

void UPauseWidget::ExitButtonClick()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}

void UPauseWidget::OptionButtononClick()
{
	OptionWidgetUIObject = CreateWidget<UGameOptionWidget>(GetWorld(), OptionWidgetClass);
	OptionWidgetUIObject->AddToViewport();

	RemoveFromParent();
}
