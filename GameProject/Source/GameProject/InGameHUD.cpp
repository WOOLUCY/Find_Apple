// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameHUD.h"
#include "TimeWidget.h"


AInGameHUD::AInGameHUD()
{
	ConstructorHelpers::FClassFinder<UTimeWidget>  TimeWidgetObject(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Time/Time.Time_C'"));
	if (TimeWidgetObject.Succeeded())
	{
		TimeWidgetClass = TimeWidgetObject.Class;
	}
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
	if (TimeWidgetClass)
	{
		TimeWidget = CreateWidget<UTimeWidget>(GetWorld(), TimeWidgetClass);
		if (TimeWidget)
		{
			TimeWidget->AddToViewport();
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
