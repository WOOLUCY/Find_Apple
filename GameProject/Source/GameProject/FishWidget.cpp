// Fill out your copyright notice in the Description page of Project Settings.


#include "FishWidget.h"

#include "FindAppleCharacter.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"


void UFishWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UFishWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (Success)
		return true;

	return false;
}

void UFishWidget::UpdateFishingProgress()
{
	AFindAppleCharacter* MyChar = Cast<AFindAppleCharacter>(GetOwningPlayerPawn());

	// 낚싯대를 들고 있고, 물고기가 감지된 상황
	if(MyChar->GetIsFishDetected()&& MyChar->GetEquipNum()== 4)
	{
		BubbleImage->SetOpacity(1.f);

		float percent = (MyChar->GetFishingWaitTime()) / (MyChar->GetMaxFishingWaitTime());
		FishProgressBar->SetPercent(percent);
	}
	else
	{
		FishProgressBar->SetPercent(0.f);
		BubbleImage->SetOpacity(0.f);
	}

}
