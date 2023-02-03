// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameHUD.h"


AInGameHUD::AInGameHUD()
{

}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();
	if (ToolWidgetClass)
	{
		ToolWidget = CreateWidget<UToolWidget>(GetWorld(), ToolWidgetClass);
		if (ToolWidget)
		{
			ToolWidget->AddToViewport();
		}
	}
}

void AInGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AInGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AInGameHUD::UpdateComboCount(int32 Value)
{
	if (ToolWidget)
	{
		ToolWidget->
			UpdateComboCount(Value);
	}
}

void AInGameHUD::ResetCombo()
{
	if (ToolWidget)
	{
		ToolWidget->ResetCombo();
	}
}
