// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackScreenBegin.h"

UBlackScreenBegin::UBlackScreenBegin(const FObjectInitializer& objectInitializer): Super(objectInitializer)
{
}

void UBlackScreenBegin::NativeConstruct()
{
	Super::NativeConstruct();
	PlayAnimation(BlackScreenEnd);
}

void UBlackScreenBegin::EndAnimation()
{
	PlayAnimation(BlackScreenEnd);
}

void UBlackScreenBegin::BeginAnimation()
{
	PlayAnimation(BlackScreenBegin);
}
