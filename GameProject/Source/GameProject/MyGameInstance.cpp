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

