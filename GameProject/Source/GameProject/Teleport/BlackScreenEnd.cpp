// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackScreenEnd.h"

UBlackScreenEnd::UBlackScreenEnd(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void UBlackScreenEnd::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(BlackScreenEnd);
}
