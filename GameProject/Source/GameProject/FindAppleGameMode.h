// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FindApplePlayerController.h"
#include "FindAppleGameMode.generated.h"

/**
 * 
 */


//struct Day {
//	int Days;
//	int Hours;
//	int Minutes;
//};
UCLASS()
class GAMEPROJECT_API AFindAppleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFindAppleGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void BeginPlay() override;

	//UPROPERTY()
	//FTimespan GameTime;
	//UPROPERTY()
	//double TotalGameTime;
	//UPROPERTY()
	//FString TotalGameTimeString;
	//UPROPERTY()
	//FString GameTimeStirng;
	//UPROPERTY()
	//FTimespan TimeFormatter;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
	//void SetGameTime(float DeltaTime);

	//UFUNCTION()
	//FString GetGameTime();


private:
	// Day Today;

};
