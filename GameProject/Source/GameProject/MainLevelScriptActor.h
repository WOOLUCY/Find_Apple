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
	virtual void BeginPlay() override;

private:
	// Black Screen Pop Widget (begin, end)
	//UPROPERTY()
	//TSubclassOf<class UUserWidget> BlackScreenBeginClass;
	//UPROPERTY()
	//class UBlackScreenBegin* BlackScreenBeginUIObject;
	// Begin Widget은 쓸 일이 없어서 일단 주석 처리해 둠
	UPROPERTY()
	TSubclassOf<class UUserWidget> BlackScreenEndClass;
	UPROPERTY()
	class UBlackScreenEnd* BlackScreenEndUIObject;
};
