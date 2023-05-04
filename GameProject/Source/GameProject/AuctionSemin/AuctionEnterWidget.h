// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuctionEnterWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UAuctionEnterWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UAuctionEnterWidget(const FObjectInitializer& objectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UAuctionMenuTab* InventoryAllItem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UAuctionSelectSlot* SelectItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	FText DescriptText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AllAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SelectItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* CountTextBox = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* AmountTextBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* CloseButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* EnterButton;

	UPROPERTY(EditAnywhere)
	int32 ItemCount = 0;

	UPROPERTY(EditAnywhere)
	int32 ItemAmount = 0;

	UPROPERTY(EditAnywhere)
	int32 iAllAmount = 0;

	UFUNCTION()
	void ClickedCloseButton();
	UFUNCTION()
	void ClickedEnterButton();
	UFUNCTION()
	void ChangedAmountTextBox(const FText& Text);
	UFUNCTION()
	void ChangedCountTextBox(const FText& Text);
};
