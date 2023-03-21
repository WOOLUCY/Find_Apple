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

};
