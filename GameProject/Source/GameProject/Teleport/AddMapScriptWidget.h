// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AddMapScriptWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UAddMapScriptWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAddMapScriptWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;
};
