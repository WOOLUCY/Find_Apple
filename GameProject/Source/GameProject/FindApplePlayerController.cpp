// Fill out your copyright notice in the Description page of Project Settings.


#include "FindApplePlayerController.h"
#include "Blueprint/UserWidget.h"


void AFindApplePlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	//bEnableClickEvents = true;
	//bEnableTouchEvents = true;
	//bEnableMouseOverEvents = true;
	//bEnableTouchOverEvents = true;
	//bShowMouseCursor = true;

	//bShowMouseCursor = false;
}

void AFindApplePlayerController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

}


void AFindApplePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}