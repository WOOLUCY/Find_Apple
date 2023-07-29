// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ClientSocket.h"

#include "MyGameInstance.generated.h"

/**
 * 
 */

class Day {
private:
	int days;
	int hours;
	int minutes;
	int seconds;
	double TotalGameTime;


public:
	void SetTime(int Day, int Hour, int Min, int Sec, double total);


	void SetDay(int a) { days = a; }
	void SetHour(int a) { hours = a; }
	void SetMin(int a) { minutes = a; }
	void SetSec(int a) { seconds = a; }
	void SetTotal(int a) { TotalGameTime = a; }

	int GetDays() { return days; }
	int GetHours() {return hours; }
	int GetMin() { return minutes; }
	int GetSec() { return seconds; }
	double GetTotal() { return TotalGameTime; }

	
};
UCLASS()
class GAMEPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();
	Day Today;

	ClientSocket MySocket;

	int plantType = 7;

	FRotator Sun{ 0,180.f,180.f };
	void SetCharLoc(FVector Loc);
	FVector GetCharLoc() { return CharLoc; };
private:
	FVector CharLoc{ 0,0,0 };


	
	
};
