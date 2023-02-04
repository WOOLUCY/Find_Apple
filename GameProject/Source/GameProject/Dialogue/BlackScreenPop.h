// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BlackScreenPop.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UBlackScreenPop : public UUserWidget
{
	GENERATED_BODY()

public:
	UBlackScreenPop(const FObjectInitializer& objectInitializer);

	UPROPERTY(BlueprintReadOnly, Transient, Category = "GsUI", meta = (BindWidgetAnim))
	class UWidgetAnimation* MyOpacityAnimation;

	virtual void NativeConstruct() override;
};
