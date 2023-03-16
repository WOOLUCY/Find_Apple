// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "StartLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API AStartLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AStartLevelScriptActor();

	virtual void BeginPlay() override;

private:
	/* Start Widget Class */
	UPROPERTY()
	TSubclassOf<class UUserWidget> GameStartWidgetClass;
	UPROPERTY()
	class UGameStartWidget* GameStartUIObject;
};
