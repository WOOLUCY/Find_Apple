// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftingItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UCraftingItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCraftingItemWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* CreateButton;

	//UFUNCTION()
	//void ClickedAXButton();
};
