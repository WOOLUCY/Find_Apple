// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::SetHealthBarProgress(float MaxHealth, float CurrentHealth)
{
	HealthBar->SetPercent(CurrentHealth / MaxHealth);	
}
