// Fill out your copyright notice in the Description page of Project Settings.


#include "FishingWidget.h"

UFishingWidget::UFishingWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

void UFishingWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFishingWidget::StartFishingAnimation()
{
	PlayAnimation(FishingAnimation);
}

void UFishingWidget::StartFailAnimation()
{
	PlayAnimation(FailAnimation);
}

void UFishingWidget::StartBeginAnimation()
{
	PlayAnimation(BeginAnimation);
}
