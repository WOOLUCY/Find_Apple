// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolWidget.h"
#include "FindAppleCharacter.h"

void UToolWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UToolWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (Success)
	{
		return true;
	}

	return false;
}

void UToolWidget::UpdateToolImage()
{
	AFindAppleCharacter* MyChar = Cast<AFindAppleCharacter>(GetOwningPlayerPawn());

	if (MyChar->GetEquipNum() == 1)
	{
		HandImg->SetOpacity(0.f);
		SwordImg->SetOpacity(1.f);
		AxeImg->SetOpacity(0.f);
		PickImg->SetOpacity(0.f);
	}
	else if (MyChar->GetEquipNum() == 2)
	{
		HandImg->SetOpacity(0.f);
		SwordImg->SetOpacity(0.f);
		AxeImg->SetOpacity(1.f);
		PickImg->SetOpacity(0.f);
	}
	else if (MyChar->GetEquipNum() == 3)
	{
		HandImg->SetOpacity(0.f);
		SwordImg->SetOpacity(0.f);
		AxeImg->SetOpacity(0.f);
		PickImg->SetOpacity(1.f);
	}
	else
	{
		HandImg->SetOpacity(1.f);
		SwordImg->SetOpacity(0.f);
		AxeImg->SetOpacity(0.f);
		PickImg->SetOpacity(0.f);
	}


}
