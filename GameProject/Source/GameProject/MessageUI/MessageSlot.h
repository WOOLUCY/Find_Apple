// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageSlot.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UMessageSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UMessageSlot(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* SlotButton;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SenderText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DetailText;

	UPROPERTY()
	FText ScriptText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMessageListUI* MessageListUIWidget;

private:
	UFUNCTION()
	void SlotButtonClick();
};
