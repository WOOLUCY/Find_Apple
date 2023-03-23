// Fill out your copyright notice in the Description page of Project Settings.


#include "HungerWidget.h"
#include "FindAppleCharacter.h"

#include "Components/ProgressBar.h"


//UHungerWidget::UHungerWidget(const FObjectInitializer& objectInitializer)
//{
//}

void UHungerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DoOnce.Reset();
}

bool UHungerWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (Success)
		return true;

	return false;
}

void UHungerWidget::UpdateHunger()
{
	AFindAppleCharacter* MyChar = Cast<AFindAppleCharacter>(GetOwningPlayerPawn());

	float percent = (MyChar->GetCurHunger()) / (MyChar->GetMaxHunger());
	HungerBar->SetPercent(percent);

	if (PrevHunger != MyChar->GetCurHunger() && DoOnce.Execute())
	{
		PlayAnimation(HungerAnimation);
		UE_LOG(LogClass, Warning, TEXT("Player's Current Hunger:%f"), MyChar->GetCurHunger());
		PrevHunger = MyChar->GetCurHunger();
	}

	else if (PrevHunger == MyChar->GetCurHunger())
		DoOnce.Reset();
}