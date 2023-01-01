// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameProjectGameMode.h"
#include "GameProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameProjectGameMode::AGameProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
