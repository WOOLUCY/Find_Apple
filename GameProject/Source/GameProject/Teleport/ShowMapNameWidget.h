// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShowMapNameWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UShowMapNameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UShowMapNameWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NameText;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Animation", meta = (BindWidgetAnim))
	class UWidgetAnimation* MoveBorderShow;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Animation", meta = (BindWidgetAnim))
	class UWidgetAnimation* MoveBorderHidden;
};
