// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DoOnce.h"
#include "HungerWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UHungerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//UHungerWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer);

	virtual void NativeConstruct() override;

	bool Initialize() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* HungerBar;

	/* Animation */
	UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* HungerAnimation;

	UPROPERTY(VisibleAnywhere)
		FDoOnce DoOnce;

	float PrevHunger = 100.f;

	void UpdateHunger();
};
