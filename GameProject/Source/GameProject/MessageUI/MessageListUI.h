// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageListUI.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UMessageListUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UMessageListUI(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UScrollBox* MessageList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* SendButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* AllBorder;

	UFUNCTION()
	void CloseButtonClick();

	UFUNCTION()
	void Refresh();

private:
	UPROPERTY()
	TSubclassOf<class UUserWidget> MessageSlotWidgetClass;
	UPROPERTY()
	class UMessageSlot* MessageSlotWidgetUIObject;
	
	UPROPERTY()
	TSubclassOf<class UUserWidget> SendMessageWidgetClass;
	UPROPERTY()
	class UMessageSendUI* SendMessageWidgetUIObject;
	
	UFUNCTION()
	void CreateSendMessageWidget();
};
