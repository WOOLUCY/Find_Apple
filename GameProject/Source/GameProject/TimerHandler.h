// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGameInstance.h"

#include "TimerHandler.generated.h"



UCLASS()
class GAMEPROJECT_API ATimerHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimerHandler();
	
	//데모때라 4000으로 바꿔놓음
	const float speed = 10000.f;
	
	UPROPERTY()
		double TotalGameTime;
	UPROPERTY()
		FString TotalGameTimeString;
	UPROPERTY()
		FString GameTimeStirng;
	UPROPERTY()
		FTimespan TimeFormatter;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SetGameTime(float DeltaTime);

	UFUNCTION()
		FString GetGameTime();

	Day Today;
	FRotator SunRotation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason )override;

public:	

};
