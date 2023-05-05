// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BlackScreenBegin.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UBlackScreenBegin : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBlackScreenBegin(const FObjectInitializer& objectInitializer);

	UPROPERTY(BlueprintReadOnly, Transient, Category = "Animation", meta = (BindWidgetAnim))
	class UWidgetAnimation* BlackScreenBegin;

	virtual void NativeConstruct() override;
};
