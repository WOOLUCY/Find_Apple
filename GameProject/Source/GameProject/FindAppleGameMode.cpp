// Fill out your copyright notice in the Description page of Project Settings.


#include "FindAppleGameMode.h"
#include "Dialogue/DialogueDataStruct.h"
#include "FindAppleCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "InGameHUD.h"

AFindAppleGameMode::AFindAppleGameMode()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HUDClass = AInGameHUD::StaticClass();
	DefaultPawnClass = AFindAppleCharacter::StaticClass();
	PlayerControllerClass = AFindApplePlayerController::StaticClass();
}

void AFindAppleGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AFindAppleGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AFindAppleGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
