// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UMessageHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMessageHudWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MessageListWidgetClass;

	UPROPERTY()
	class UMessageListUI* MessageListWidgetUIObject;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* MessageButton;

	UFUNCTION()
	void MessageButtonClick();
	UFUNCTION()
	void ActiveMessageButton();
	UFUNCTION()
	void DisableMessageButton();
};
