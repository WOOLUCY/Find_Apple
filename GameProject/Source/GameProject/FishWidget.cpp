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

	if(MyChar->GetIsFishing()&& MyChar->GetEquipNum()== 4)
	{
		BubbleImage->SetOpacity(1.f);
	}
	else
	{
		FishProgressBar->SetPercent(0.f);
		BubbleImage->SetOpacity(0.f);
	}
}
