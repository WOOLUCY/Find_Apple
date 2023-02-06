// Fill out your copyright notice in the Description page of Project Settings.


#include "FindApplePlayerController.h"
#include "Blueprint/UserWidget.h"


void AFindApplePlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchOverEvents = true;
	bShowMouseCursor = true;

	//bShowMouseCursor = false;
}

void AFindApplePlayerController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

}

void AFindApplePlayerController::changeMouse()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("pressed A"));

}

void AFindApplePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (InputKey(EKeys::B, EInputEvent::IE_Pressed, 1.0f, false)) {
		changeMouse();
	}
	//InputComponent->BindKey(EKeys::B, IE_Pressed, this, &AFindApplePlayerController::changeMouse);
}
