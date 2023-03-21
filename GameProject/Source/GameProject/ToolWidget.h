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
	bool Initialize() override;

	// TODO: Combo 관련 함수 삭제
	void UpdateComboCount(int32 Value);
	//void UpdateHeartCount(float DeltaSeconds);
	void UpdateToolImage();

	void ResetCombo();

	/* Tool */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* SwordImg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* PickImg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* AxeImg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* HandImg;

	/* Heart */
	// TODO: 체력 위젯 프로그레스 바로 변경
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UImage* HeartImg_01;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UImage* HeartImg_02;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UImage* HeartImg_03;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UImage* HeartImg_04;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UImage* HeartImg_05;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UImage* HeartImg_06;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UImage* HeartImg_07;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UImage* HeartImg_08;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UImage* HeartImg_09;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//class UImage* HeartImg_10;

};
