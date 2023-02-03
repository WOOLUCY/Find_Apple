// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolWidget.h"

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
	if (TXTCombo && Value > 1)
	{
		// turn textbox visible if already hidden
		if (TXTCombo->Visibility == ESlateVisibility::Hidden)
		{
			TXTCombo->SetVisibility(ESlateVisibility::Visible);
		}
		// generate output like 2x Combo
		TXTCombo->SetText(FText::FromString(FString::FromInt(Value) + "x Combo"));
	}
}

void UToolWidget::ResetCombo()
{

}
