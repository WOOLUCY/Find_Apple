// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerHandler.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATimerHandler::ATimerHandler()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void ATimerHandler::BeginPlay()
{
	Super::BeginPlay();

	auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance != nullptr) {
		Day temp = GameInstance->Today;

		Today.SetTime(temp.GetDays(), temp.GetHours(), temp.GetMin(), temp.GetSec(),temp.GetTotal());
		TotalGameTime = Today.GetTotal();

		UE_LOG(LogTemp, Warning, TEXT("Begin Plyat %d %d"), Today.GetDays(), Today.GetHours());


	}
}

void ATimerHandler::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("End Plyat %d %d"), Today.GetDays(), Today.GetHours());
		GameInstance->Today.SetTime(Today.GetDays(), Today.GetHours(), Today.GetMin(), Today.GetSec(),Today.GetTotal());
	}



}

// Called every frame
void ATimerHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetGameTime(DeltaTime);

}



void ATimerHandler::SetGameTime(float DeltaTime)
{
	TotalGameTime += DeltaTime * 2000;

	if (Today.GetDays() < TimeFormatter.GetDays()) {
		Today.SetDay(TimeFormatter.GetDays());

	}
	if (Today.GetHours() == 23) {
		TotalGameTime = 0;
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("TotalTime==12"));
		Today.SetDay(Today.GetDays()+1);
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("realdkfjdk??"));

	}

	TimeFormatter = FTimespan(Today.GetDays(), 8 , 0, FMath::Floor(TotalGameTime), FMath::Floor(FMath::Fmod(TotalGameTime, 1.0f) * 1000.0f));
	TotalGameTimeString = TimeFormatter.ToString();


	Today.SetHour( TimeFormatter.GetHours());
	Today.SetMin( TimeFormatter.GetMinutes());
	Today.SetSec(TimeFormatter.GetSeconds());
	Today.SetTotal(TotalGameTime);


	TArray< FStringFormatArg > args;
	args.Add(FStringFormatArg(FString::FromInt(TimeFormatter.GetDays())));
	args.Add(FStringFormatArg(FString::FromInt(TimeFormatter.GetHours())));
	args.Add(FStringFormatArg(FString::FromInt(TimeFormatter.GetMinutes())));
	args.Add(FStringFormatArg(FString::FromInt(TimeFormatter.GetSeconds())));

	GameTimeStirng = FString::Format(TEXT("Day {0} | {1}:{2}:{3}"), args);

}

FString ATimerHandler::GetGameTime()
{
	return GameTimeStirng;
}
