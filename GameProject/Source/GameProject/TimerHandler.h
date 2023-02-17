// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerHandler.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FTimeChangeDelegate, int32, int32)

UCLASS()
class GAMEPROJECT_API ATimerHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimerHandler();
	
	FTimeChangeDelegate PlantDelegate;

	UPROPERTY()
		int32 TimeScale;


	UPROPERTY()
		int32 Hours;

	UPROPERTY()
		int32 Minutes;

	UPROPERTY()
		FTimespan GameTime;



	UPROPERTY()
		float ElapsedSecond;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
