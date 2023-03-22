// Fill out your copyright notice in the Description page of Project Settings.


#include "HPWidget.h"
#include "FindAppleCharacter.h"
#include "Components/ProgressBar.h"

void UHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UHPWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (Success)	
		return true;

	return false;
}

void UHPWidget::UpdateHP()
{
	AFindAppleCharacter* MyChar = Cast<AFindAppleCharacter>(GetOwningPlayerPawn());

	float percent = (MyChar->GetCurHealth()) / (MyChar->GetMaxHealth());
	HPBar->SetPercent(percent);

	// �ǰ� �� ���� �ִϸ��̼� ���
	if (MyChar->GetIsAttacked())
		PlayHPWidgetAnimation();
}

void UHPWidget::PlayHPWidgetAnimation()
{
	PlayAnimation(HPWidgetAnimation);
}

void UHPWidget::StopHPWidgetAnimation()
{
	StopAnimation(HPWidgetAnimation);
}
