// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UDialogueWidget(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

	void ChangeText(FText Name, FText Dialogue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DialogueTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NameTextBlock;

};
