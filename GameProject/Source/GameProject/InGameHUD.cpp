// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameHUD.h"

#include "FindAppleCharacter.h"
#include "TimeWidget.h"
#include "ToolWidget.h"
#include "HungerWidget.h"
#include "HPWidget.h"


AInGameHUD::AInGameHUD()
{
	ConstructorHelpers::FClassFinder<UTimeWidget>  TimeWidgetObject(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Time/Time.Time_C'"));
	if (TimeWidgetObject.Succeeded())
	{
		TimeWidgetClass = TimeWidgetObject.Class;
	}

	ConstructorHelpers::FClassFinder<UHPWidget> HPWidgetObject(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Woo/UI/HPWidget.HPWidget_C'"));
	if (HPWidgetObject.Succeeded())
	{
		HPWidgetClass = HPWidgetObject.Class;
	}

	ConstructorHelpers::FClassFinder<UToolWidget> ToolWidgetObject(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Woo/UI/ToolWidget.ToolWidget_C'"));
	if (ToolWidgetObject.Succeeded())
	{
		ToolWidgetClass = ToolWidgetObject.Class;
	}

	ConstructorHelpers::FClassFinder<UHungerWidget> HungerWidgetObject(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Woo/UI/HungerWidget.HungerWidget_C'"));
	if (HungerWidgetObject.Succeeded())
	{
		HungerWidgetClass = HungerWidgetObject.Class;
	}

}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HPWidgetClass)
	{
		HPWidget = CreateWidget<UHPWidget>(GetWorld(), HPWidgetClass);
		if (HPWidget)
		{
			HPWidget->AddToViewport();
		}
	}
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
	if (HungerWidgetClass)
	{
		HungerWidget = CreateWidget<UHungerWidget>(GetWorld(), HungerWidgetClass);
		if (HungerWidget)
		{
			HungerWidget->AddToViewport();
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

	UpdateHeartCount();
	UpdateToolImage();
	UpdateHunger();
}

void AInGameHUD::UpdateHeartCount()
{
	if (HPWidget)
	{
		HPWidget->UpdateHP();
	}
}

void AInGameHUD::UpdateHunger()
{
	if (HungerWidget)
	{
		// TODO: 허기 위젯 바인딩 수정
		HungerWidget->UpdateHunger();
	}
}

void AInGameHUD::UpdateToolImage()
{
	if (ToolWidget)
	{
		ToolWidget->UpdateToolImage();
	}
}
