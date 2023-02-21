// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BlackScreenEnd.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UBlackScreenEnd : public UUserWidget
{
	GENERATED_BODY()


public:
	UBlackScreenEnd(const FObjectInitializer& objectInitializer);

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Animation", meta = (BindWidgetAnim))
	class UWidgetAnimation* BlackScreenEnd;

	virtual void NativeConstruct() override;
};
