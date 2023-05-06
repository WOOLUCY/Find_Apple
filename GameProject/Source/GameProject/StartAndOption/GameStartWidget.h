// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStartWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UGameStartWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UGameStartWidget(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* TitleImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* OptionButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(EditAnywhere, category = "Setting", meta = (AllowPrivateAccess = "true"))
    FName TransferLevelName = "CopyEditMap1";

private:
	/* Black Screen Pop (어두워지는 효과) */
	/* Begin */
	UPROPERTY()
	TSubclassOf<class UUserWidget> BlackScreenBeginClass;
	UPROPERTY()
	class UBlackScreenBegin* BlackScreenBeginUIObject;
	/* End */
	UPROPERTY()
	TSubclassOf<class UUserWidget> BlackScreenEndClass;
	UPROPERTY()
	class UBlackScreenEnd* BlackScreenEndUIObject;

	UPROPERTY()
	TSubclassOf<class UUserWidget> OptionWidgetClass;
	UPROPERTY()
	class UGameOptionWidget* OptionUIObject;
	
public:
	UFUNCTION()
	void CreateOptionWidget();

private:
	UFUNCTION()
	void GameStart();
	UFUNCTION()
	void BlackScreenPopStart();
	UFUNCTION()
	void BlackScreenPopEnd();
	UFUNCTION()
	void ChangeLevelAndDestroy();
};
