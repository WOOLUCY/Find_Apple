// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowMapNameWidget.h"

UShowMapNameWidget::UShowMapNameWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void UShowMapNameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(MoveBorderShow);
}
