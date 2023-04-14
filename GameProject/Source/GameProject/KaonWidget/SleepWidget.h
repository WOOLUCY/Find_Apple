// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SleepWidget.generated.h"

/**
 * 
 */

DECLARE_DELEGATE(AboutSleepDelegate)

UCLASS()
class GAMEPROJECT_API USleepWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	
	UFUNCTION()
		void YesChoice();

	UFUNCTION()
		void NoChoice();



	AboutSleepDelegate YesDelegate;
	AboutSleepDelegate NoDelegate;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
		class UButton* YesButton;

	UPROPERTY()
		class UButton* NoButton;

};
