// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FindApplePlayerController.h"
#include "FindAppleGameMode.generated.h"

/**
 * 
 */


UCLASS()
class GAMEPROJECT_API AFindAppleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFindAppleGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void BeginPlay() override;

private:

public:
};
