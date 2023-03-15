// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolWidget.h"
#include "FindAppleCharacter.h"

void UToolWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

//UToolWidget::UToolWidget(const FObjectInitializer& ObjectInitalizer)
//{
//
//}

void UToolWidget::UpdateComboCount(int32 Value)
{
	//if (TXTCombo && Value > 1)
	//{
	//	// turn textbox visible if already hidden
	//	if (TXTCombo->Visibility == ESlateVisibility::Hidden)
	//	{
	//		TXTCombo->SetVisibility(ESlateVisibility::Visible);
	//	}
	//	// generate output like 2x Combo
	//	TXTCombo->SetText(FText::FromString(FString::FromInt(Value) + "x Combo"));
	//}
}

void UToolWidget::UpdateHeartCount()
{
	AFindAppleCharacter* MyChar = Cast<AFindAppleCharacter>(GetOwningPlayerPawn());
	//auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	//if (MyChar->CurHealth == 200.f)
	//{
	//	SwordImg->SetVisibility(ESlateVisibility::Hidden);
	//	UE_LOG(LogClass, Warning, TEXT("Player's HP Is FULL"));
	//}

}

void UToolWidget::UpdateToolImage()
{
	AFindAppleCharacter* MyChar = Cast<AFindAppleCharacter>(GetOwningPlayerPawn());

	if (MyChar->CurEquipNum == 1)
	{
		SwordImg->SetOpacity(1.f);
		AxeImg->SetOpacity(0.f);
		PickImg->SetOpacity(0.f);
	}
	else if (MyChar->CurEquipNum == 2)
	{
		SwordImg->SetOpacity(0.f);
		AxeImg->SetOpacity(1.f);
		PickImg->SetOpacity(0.f);
	}
	else if (MyChar->CurEquipNum == 3)
	{
		SwordImg->SetOpacity(0.f);
		AxeImg->SetOpacity(0.f);
		PickImg->SetOpacity(1.f);
	}
	else
	{
		SwordImg->SetOpacity(0.f);
		AxeImg->SetOpacity(0.f);
		PickImg->SetOpacity(0.f);
	}

	//if (MyChar->CurEquipNum == 1)
	//{
	//	SwordImg->SetVisibility(ESlateVisibility::Visible);
	//	AxeImg->SetVisibility(ESlateVisibility::Hidden);
	//	PickImg->SetVisibility(ESlateVisibility::Hidden);
	//}
	//else if (MyChar->CurEquipNum == 2)
	//{
	//	SwordImg->SetVisibility(ESlateVisibility::Hidden);
	//	AxeImg->SetVisibility(ESlateVisibility::Visible);
	//	PickImg->SetVisibility(ESlateVisibility::Hidden);
	//}
	//else if (MyChar->CurEquipNum == 3)
	//{
	//	SwordImg->SetVisibility(ESlateVisibility::Hidden);
	//	AxeImg->SetVisibility(ESlateVisibility::Hidden);
	//	PickImg->SetVisibility(ESlateVisibility::Visible);
	//}
	//else if (MyChar->CurEquipNum == 0)
	//{
	//	SwordImg->SetVisibility(ESlateVisibility::Hidden);
	//	AxeImg->SetVisibility(ESlateVisibility::Hidden);
	//	PickImg->SetVisibility(ESlateVisibility::Hidden);
	//}
}

void UToolWidget::ResetCombo()
{

}
