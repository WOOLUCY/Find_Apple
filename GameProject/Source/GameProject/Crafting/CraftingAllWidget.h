// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftingAllWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UCraftingAllWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCraftingAllWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* AXButton;

	UFUNCTION()
	void ClickedAXButton();
};
