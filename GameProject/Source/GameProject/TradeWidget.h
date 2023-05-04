// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TradeWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UTradeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	/* �Ǹ��ϱ� ��ư */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* TradeButton;

	/* �����ϱ� ��ư */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BuyButton01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BuyButton02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BuyButton03;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BuyButton04;


	/* ǰ�� �̹��� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Item01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Item02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Item03;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Item04;

public:
	/* Click Action */
	UFUNCTION()
		void TradeButtonClick();

	UFUNCTION()
		void BuyButton01Click();

	UFUNCTION()
		void BuyButton02Click();

	UFUNCTION()
		void BuyButton03Click();

	UFUNCTION()
		void BuyButton04Click();

};
