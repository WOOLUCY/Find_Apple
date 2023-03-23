// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UGameOptionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UGameOptionWidget(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

public:
	/* 화면 크기 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* FullScreenBtn;
	UFUNCTION()
	void SetFullScreen();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* WindowBtn;
	UFUNCTION()
	void SetWindowScreen();

	/* 프레임 설정 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* FPS30Btn;
	UFUNCTION()
	void Set30FPS();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* FPS60Btn;
	UFUNCTION()
	void Set60FPS();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* FPS120Btn;
	UFUNCTION()
	void Set120FPS();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* FPSBtn;
	UFUNCTION()
	void SetUnlimitFPS();

	/* 뷰 디스턴스 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ViewMedium;
	UFUNCTION()
	void SetViewMedium();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ViewNear;
	UFUNCTION()
	void SetViewNear();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ViewFar;
	UFUNCTION()
	void SetViewFar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ViewEpic;
	UFUNCTION()
	void SetViewEpic();

	/* 포스트 프로세싱 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* PostLow;
	UFUNCTION()
	void SetPostLow();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* PostMedium;
	UFUNCTION()
	void SetPostMedium();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* PostHigh;
	UFUNCTION()
	void SetPostHigh();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* PostEpic;
	UFUNCTION()
	void SetPostEpic();

	/* 안티 앨리어싱 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* AntiLow;
	UFUNCTION()
	void SetAntiLow();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* AntiMedium;
	UFUNCTION()
	void SetAntiMedium();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* AntiHigh;
	UFUNCTION()
	void SetAntiHigh();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* AntiEpic;
	UFUNCTION()
	void SetAntiEpic();

	/* 텍스처 퀄리티 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* TextureLow;
	UFUNCTION()
	void SetTextureLow();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* TextureMedium;
	UFUNCTION()
	void SetTextureMedium();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* TextureHigh;
	UFUNCTION()
	void SetTextureHigh();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* TextureEpic;
	UFUNCTION()
	void SetTextureEpic();

	/* 섀도우 퀄리티 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ShadowLow;
	UFUNCTION()
	void SetShadowLow();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ShadowMedium;
	UFUNCTION()
	void SetShadowMedium();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ShadowHigh;
	UFUNCTION()
	void SetShadowHigh();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ShadowEpic;
	UFUNCTION()
	void SetShadowEpic();

	/*  뒤로 가기 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* CloseButton;
	UFUNCTION()
	void WidgetClose();

	UPROPERTY()
	UGameUserSettings* setting;
};
