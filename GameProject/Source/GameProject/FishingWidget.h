// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FishingWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UFishingWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UFishingWidget(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Animation", meta = (BindWidgetAnim))
	class UWidgetAnimation* FishingAnimation;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Animation", meta = (BindWidgetAnim))
	class UWidgetAnimation* FailAnimation;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Animation", meta = (BindWidgetAnim))
	class UWidgetAnimation* BeginAnimation;

	void StartFishingAnimation();
	void StartFailAnimation();
	void StartBeginAnimation();
};
