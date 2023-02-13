// Fill out your copyright notice in the Description page of Project Settings.


#include "FindAppleGameMode.h"
#include "Dialogue/DialogueDataStruct.h"
#include "FindAppleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFindAppleGameMode::AFindAppleGameMode()
{
	DefaultPawnClass = AFindAppleCharacter::StaticClass();
	PlayerControllerClass = AFindApplePlayerController::StaticClass();

}

void AFindAppleGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AFindAppleGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
