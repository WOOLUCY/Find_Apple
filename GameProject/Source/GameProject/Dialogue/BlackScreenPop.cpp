// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackScreenPop.h"
#include "Animation/WidgetAnimation.h"

UBlackScreenPop::UBlackScreenPop(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

void UBlackScreenPop::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(MyOpacityAnimation);
	//DialogueTextBlock->SetText(FText::FromString("wqwqwqwqwqwq"));
}