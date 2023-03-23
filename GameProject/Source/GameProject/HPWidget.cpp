// Fill out your copyright notice in the Description page of Project Settings.


#include "HPWidget.h"
#include "FindAppleCharacter.h"
#include "Components/ProgressBar.h"

void UHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DoOnce.Reset();
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

	// 피격 시 위젯 애니메이션 재생
	float percent = (MyChar->GetCurHealth()) / (MyChar->GetMaxHealth());

	if (MyChar->GetIsAttacked() && DoOnce.Execute())
	{
		UE_LOG(LogClass, Warning, TEXT("Widget Animation Is Playing"));
		PlayHPWidgetAnimation();
	}

	else if (!MyChar->GetIsAttacked())
	{
		DoOnce.Reset();
	}

	HPBar->SetPercent(percent);

}

void UHPWidget::PlayHPWidgetAnimation()
{
	PlayAnimation(HPWidgetAnimation);
}

void UHPWidget::StopHPWidgetAnimation()
{
	StopAnimation(HPWidgetAnimation);
}
