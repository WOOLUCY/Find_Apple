// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftingListWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UCraftingListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCraftingListWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NeedCnt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HaveCnt;
};
