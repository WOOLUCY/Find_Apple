// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void Day::SetTime(int Day, int Hour, int Min, int Sec,double total)
{
	days = Day;
	hours = Hour;
	minutes = Min;
	seconds = Sec;
	TotalGameTime = total;
}

UMyGameInstance::UMyGameInstance()
{
	Sun = FRotator(0, 180, 180);

	//UE_LOG(LogTemp, Warning, TEXT("UMyInstance init??"));
}

void UMyGameInstance::SetCharLoc(FVector Loc)
{
	CharLoc = Loc;
}
