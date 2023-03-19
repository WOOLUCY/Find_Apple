// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PressKeyWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UPressKeyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPressKeyWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_32;
};
