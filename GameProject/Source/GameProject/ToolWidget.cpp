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

void UToolWidget::UpdateHeartCount(float DeltaSeconds)
{
	AFindAppleCharacter* MyChar = Cast<AFindAppleCharacter>(GetOwningPlayerPawn());
	//auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	//if (MyChar->CurHealth == 200.f)
	//{
	//	SwordImg->SetVisibility(ESlateVisibility::Hidden);
	//	UE_LOG(LogClass, Warning, TEXT("Player's HP Is FULL"));
	//}
	
	// TODO: 투명도 서서히 줄이기
	if (MyChar->GetCurHealth() >= 200.f)
	{
		HeartImg_10->SetOpacity(1.f);
	}
	else
	{
		HeartImg_10->SetOpacity(0.f);
	}

	if (MyChar->GetCurHealth() >= 180.f)
	{
		HeartImg_09->SetOpacity(1.f);
	}
	else
	{
		HeartImg_09->SetOpacity(0.f);
	}

	if (MyChar->GetCurHealth() >= 160.f)
	{
		HeartImg_08->SetOpacity(1.f);
	}
	else
	{
		HeartImg_08->SetOpacity(0.f);
	}

	if (MyChar->GetCurHealth() >= 140.f)
	{
		HeartImg_07->SetOpacity(1.f);
	}
	else
	{
		HeartImg_07->SetOpacity(0.f);
	}

	if (MyChar->GetCurHealth() >= 120.f)
	{
		HeartImg_06->SetOpacity(1.f);
	}
	else
	{
		HeartImg_06->SetOpacity(0.f);
	}

	if (MyChar->GetCurHealth() >= 100.f)
	{
		HeartImg_05->SetOpacity(1.f);
	}
	else
	{
		HeartImg_05->SetOpacity(0.f);
	}

	if (MyChar->GetCurHealth() >= 80.f)
	{
		HeartImg_04->SetOpacity(1.f);
	}
	else
	{
		HeartImg_04->SetOpacity(0.f);
	}

	if (MyChar->GetCurHealth() >= 60.f)
	{
		HeartImg_03->SetOpacity(1.f);
	}
	else
	{
		HeartImg_03->SetOpacity(0.f);
	}


	if (MyChar->GetCurHealth() >= 40.f)
	{
		HeartImg_02->SetOpacity(1.f);
	}
	else
	{
		HeartImg_02->SetOpacity(0.f);
	}


	if (MyChar->GetCurHealth() >= 20.f)
	{
		HeartImg_01->SetOpacity(1.f);
	}
	else
	{
		HeartImg_01->SetOpacity(0.f);
	}
}

void UToolWidget::UpdateToolImage()
{
	AFindAppleCharacter* MyChar = Cast<AFindAppleCharacter>(GetOwningPlayerPawn());

	if (MyChar->GetEquipNum() == 1)
	{
		SwordImg->SetOpacity(1.f);
		AxeImg->SetOpacity(0.f);
		PickImg->SetOpacity(0.f);
	}
	else if (MyChar->GetEquipNum() == 2)
	{
		SwordImg->SetOpacity(0.f);
		AxeImg->SetOpacity(1.f);
		PickImg->SetOpacity(0.f);
	}
	else if (MyChar->GetEquipNum() == 3)
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


}

void UToolWidget::ResetCombo()
{

}
