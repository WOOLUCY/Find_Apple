// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AddMapWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UAddMapWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAddMapWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NameText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Inves;

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Animation", meta = (BindWidgetAnim))
	class UWidgetAnimation* ShowScript;
};
