// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerHandler.h"

// Sets default values
ATimerHandler::ATimerHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	TimeScale = 30;
	Hours = 0;
	Minutes = 0;
	ElapsedSecond = 0;
	GameTime = 0;
}

// Called when the game starts or when spawned
void ATimerHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimerHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedSecond += (DeltaTime * TimeScale);
	if (ElapsedSecond > 60) {
		ElapsedSecond -= 60;
		++Minutes;
		
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Hours==1 "));

		if (Minutes > 60) {
			Minutes -= 60;
			++Hours;
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Minutes==1 "));

		}

		PlantDelegate.Broadcast(Hours,Minutes);
	}

}

