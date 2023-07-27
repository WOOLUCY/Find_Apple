// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API AMainLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
protected:
	AMainLevelScriptActor();

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

public:
	// sound 
	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundWave* backgoundMusicAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class UAudioComponent* backgoundMusicAudioComponent;

	UFUNCTION()
	void BackgroundMusicStopAndPlay();
};