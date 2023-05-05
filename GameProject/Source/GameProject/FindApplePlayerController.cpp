// Fill out your copyright notice in the Description page of Project Settings.


#include "FindApplePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"


#include "Blueprint/UserWidget.h"


AFindApplePlayerController::AFindApplePlayerController()
{

}

void AFindApplePlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AFindApplePlayerController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

}

void AFindApplePlayerController::BeginPlay()
{

	auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance != nullptr) {
		if (!GameInstance->MySocket.IsInit) {
			if (GameInstance->MySocket.InitSocket()) {
				GameInstance->MySocket.IsInit = true;
			}
		}
	}

}



void AFindApplePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}
