// Fill out your copyright notice in the Description page of Project Settings.


#include "FindAppleGameMode.h"
#include "Dialogue/DialogueDataStruct.h"
#include "FindAppleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFindAppleGameMode::AFindAppleGameMode()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	SetGameTime(DeltaTime);
}

void AFindAppleGameMode::SetGameTime(float DeltaTime)
{
	TotalGameTime += DeltaTime * 100;

	//totalGameTime += DeltaSeconds;

	TimeFormatter = FTimespan(0, 0, 0, FMath::Floor(TotalGameTime), FMath::Floor(FMath::Fmod(TotalGameTime, 1.0f) * 1000.0f));
	TotalGameTimeString = TimeFormatter.ToString();

	TArray< FStringFormatArg > args;
	args.Add(FStringFormatArg(FString::FromInt(TimeFormatter.GetDays())));
	args.Add(FStringFormatArg(FString::FromInt(TimeFormatter.GetHours())));
	args.Add(FStringFormatArg(FString::FromInt(TimeFormatter.GetMinutes())));
	args.Add(FStringFormatArg(FString::FromInt(TimeFormatter.GetSeconds())));

	GameTimeStirng = FString::Format(TEXT("Day {0} | {1}:{2}:{3}"), args);

}

FString AFindAppleGameMode::GetGameTime()
{
	return GameTimeStirng;
}

void AFindAppleGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
