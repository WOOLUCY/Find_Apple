// Fill out your copyright notice in the Description page of Project Settings.

#include "AddMapWidget.h"

UAddMapWidget::UAddMapWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void UAddMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(ShowScript);


	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			RemoveFromParent();
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), 5.1f, false);
}
