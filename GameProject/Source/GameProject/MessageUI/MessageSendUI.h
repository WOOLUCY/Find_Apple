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

	UFUNCTION()
	void CloseButtonClick();
};
