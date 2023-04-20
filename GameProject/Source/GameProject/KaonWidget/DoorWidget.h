// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DoorWidget.generated.h"

/**
 * 
 */

DECLARE_DELEGATE(AboutDoorDelegate)

UCLASS()
class GAMEPROJECT_API UDoorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void YesChoice();

	UFUNCTION()
		void NoChoice();

	AboutDoorDelegate YesDelegate;
	AboutDoorDelegate NoDelegate;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
		class UButton* YesButton;

	UPROPERTY()
		class UButton* NoButton;

	UPROPERTY()
		class UTextBlock* TextBlock;
	
};
