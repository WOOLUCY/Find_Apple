// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageInfoUI.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UMessageInfoUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMessageInfoUI(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NameTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TitleTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DetailTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* CloseButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMessageListUI* MessageListUIWidget;

private:
	UFUNCTION()
	void CloseButtonClick();
};
