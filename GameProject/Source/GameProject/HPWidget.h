// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DoOnce.h"
#include "HPWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UHPWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	bool Initialize() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HPBar;

	UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* HPWidgetAnimation;

	UPROPERTY(VisibleAnywhere)
	FDoOnce DoOnce;

	void UpdateHP();
	void PlayHPWidgetAnimation();
	void StopHPWidgetAnimation();
};
