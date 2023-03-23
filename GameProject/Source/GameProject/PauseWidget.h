// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPauseWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* OptionButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ExitButton;

	/* Option Widget */
	UPROPERTY()
	TSubclassOf<class UUserWidget> OptionWidgetClass;
	UPROPERTY()
	class UGameOptionWidget* OptionWidgetUIObject;

public:
	/* Click Action */
	UFUNCTION()
	void ResumeButtonClick();

	UFUNCTION()
	void ExitButtonClick();

	UFUNCTION()
	void OptionButtononClick();
};
