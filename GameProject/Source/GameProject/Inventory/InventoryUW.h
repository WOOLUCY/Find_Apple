// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUW.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UInventoryUW : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UInventoryUW(const FObjectInitializer& objectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInventoryMenuUW* WBP_InventoryMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInventoryToolTipUW* WBP_ToolTip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FText Descript;

	FOnInputAction Input;
};
