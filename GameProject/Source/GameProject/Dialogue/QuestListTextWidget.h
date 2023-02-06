// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestListTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UQuestListTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UQuestListTextWidget(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* WrapBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* Quest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* QuestTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* QuestDes;
};
