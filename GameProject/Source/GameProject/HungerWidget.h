// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HungerWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UHungerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UHungerWidget(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

	bool Initialize() override;

	
};
