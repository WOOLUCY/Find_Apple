// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UTimeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UTimeWidget(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

	bool Initialize() override;

	UPROPERTY( BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TimeText;

	UPROPERTY()
	FTimespan GameTime;

	UFUNCTION()
	FText SetTimeText();

};
