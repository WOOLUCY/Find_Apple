// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageSendUI.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UMessageSendUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMessageSendUI(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMessageListUI* MessageListUIWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* SendButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* NameTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* TitleTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UMultiLineEditableTextBox* DetailTextBox;

	UPROPERTY()
	FText SendID;
	UPROPERTY()
	FText DetailScript;
	UPROPERTY()
	FText Title;

private:
	UFUNCTION()
	void CloseButtonClick();
	UFUNCTION()
	void SendButtonClick();
	UFUNCTION()
	void ChangedNameTextBox(const FText& Text);
	UFUNCTION()
	void ChangedDetailTextBox(const FText& Text);
	UFUNCTION()
	void ChangedTitleTextBox(const FText& Text);
};
