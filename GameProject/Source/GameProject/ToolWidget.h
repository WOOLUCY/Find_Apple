// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "ToolWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UToolWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	//UToolWidget(const FObjectInitializer& ObjectInitalizer);

	void UpdateComboCount(int32 Value);
	void UpdateHeartCount();
	void UpdateToolImage();

	void ResetCombo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* SwordImg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* PickImg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* AxeImg;

	class UImage* HeartImg_01;
	class UImage* HeartImg_02;
	class UImage* HeartImg_03;
	class UImage* HeartImg_04;
	class UImage* HeartImg_05;
	class UImage* HeartImg_06;
	class UImage* HeartImg_07;
	class UImage* HeartImg_08;
	class UImage* HeartImg_09;
	class UImage* HeartImg_10;

};
