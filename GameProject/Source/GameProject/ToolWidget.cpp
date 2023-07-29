// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolWidget.h"
#include "FindAppleCharacter.h"

void UToolWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DoOnce.Reset();
}

bool UToolWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (Success)
	{
		return true;
	}

	//HandImg->SetOpacity(1.f);
	//SwordImg->SetOpacity(0.f);
	//AxeImg->SetOpacity(0.f);
	//PickImg->SetOpacity(0.f);

	return false;
}

void UToolWidget::UpdateToolImage()
{
	AFindAppleCharacter* MyChar = Cast<AFindAppleCharacter>(GetOwningPlayerPawn());

	if (PrevEquipNum != MyChar->GetEquipNum())
	{
		DoOnce.Reset();
	}

	if (MyChar->GetEquipNum() == 1 && DoOnce.Execute())
	{
		HandImg->SetOpacity(0.f);
		SwordImg->SetOpacity(1.f);
		AxeImg->SetOpacity(0.f);
		PickImg->SetOpacity(0.f);
		RodImg->SetOpacity(0.f);
		PlayAnimation(SwordAnimation);
		PrevEquipNum = 1;
	}
	else if (MyChar->GetEquipNum() == 2 && DoOnce.Execute())
	{
		HandImg->SetOpacity(0.f);
		SwordImg->SetOpacity(0.f);
		AxeImg->SetOpacity(1.f);
		PickImg->SetOpacity(0.f);
		RodImg->SetOpacity(0.f);
		PlayAnimation(AxeAnimation);
		PrevEquipNum = 2;
	}
	else if (MyChar->GetEquipNum() == 3 && DoOnce.Execute())
	{
		HandImg->SetOpacity(0.f);
		SwordImg->SetOpacity(0.f);
		AxeImg->SetOpacity(0.f);
		PickImg->SetOpacity(1.f);
		RodImg->SetOpacity(0.f);
		PlayAnimation(PickAnimation);
		PrevEquipNum = 3;
	}
	else if (MyChar->GetEquipNum() == 4 && DoOnce.Execute())
	{
		HandImg->SetOpacity(0.f);
		SwordImg->SetOpacity(0.f);
		AxeImg->SetOpacity(0.f);
		PickImg->SetOpacity(0.f);
		RodImg->SetOpacity(1.f);
		PlayAnimation(RodAnimation);
		PrevEquipNum = 4;
	}
	else if (MyChar->GetEquipNum()== 0 && DoOnce.Execute())
	{
		HandImg->SetOpacity(1.f);
		SwordImg->SetOpacity(0.f);
		AxeImg->SetOpacity(0.f);
		PickImg->SetOpacity(0.f);
		RodImg->SetOpacity(0.f);
		PlayAnimation(HandAnimation);
		PrevEquipNum = 0;
	}
}
