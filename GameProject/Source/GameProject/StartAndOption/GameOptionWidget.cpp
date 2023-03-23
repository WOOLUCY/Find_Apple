// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOptionWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"

UGameOptionWidget::UGameOptionWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

void UGameOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	setting = GEngine->GetGameUserSettings();

	if (setting->GetFullscreenMode() == EWindowMode::Fullscreen) {
		FullScreenBtn->SetIsEnabled(false);
	}
	else if (setting->GetFullscreenMode() == EWindowMode::Windowed) {
		WindowBtn->SetIsEnabled(false);
	}

	/* 화면 모드 */
	WindowBtn->OnClicked.AddDynamic(this, &UGameOptionWidget::SetWindowScreen);
	FullScreenBtn->OnClicked.AddDynamic(this, &UGameOptionWidget::SetFullScreen);
	// FPS
	FPS30Btn->OnClicked.AddDynamic(this, &UGameOptionWidget::Set30FPS);
	FPS60Btn->OnClicked.AddDynamic(this, &UGameOptionWidget::Set60FPS);
	FPS120Btn->OnClicked.AddDynamic(this, &UGameOptionWidget::Set120FPS);
	FPSBtn->OnClicked.AddDynamic(this, &UGameOptionWidget::SetUnlimitFPS);
	// View Distance
	ViewMedium->OnClicked.AddDynamic(this, &UGameOptionWidget::SetViewMedium);
	ViewNear->OnClicked.AddDynamic(this, &UGameOptionWidget::SetViewNear);
	ViewFar->OnClicked.AddDynamic(this, &UGameOptionWidget::SetViewFar);
	ViewEpic->OnClicked.AddDynamic(this, &UGameOptionWidget::SetViewEpic);
	// Post Processing
	PostLow->OnClicked.AddDynamic(this, &UGameOptionWidget::SetPostLow);
	PostMedium->OnClicked.AddDynamic(this, &UGameOptionWidget::SetPostMedium);
	PostHigh->OnClicked.AddDynamic(this, &UGameOptionWidget::SetPostHigh);
	PostEpic->OnClicked.AddDynamic(this, &UGameOptionWidget::SetPostEpic);
	// Anti-Aliasing
	AntiLow->OnClicked.AddDynamic(this, &UGameOptionWidget::SetAntiLow);
	AntiMedium->OnClicked.AddDynamic(this, &UGameOptionWidget::SetAntiMedium);
	AntiHigh->OnClicked.AddDynamic(this, &UGameOptionWidget::SetAntiHigh);
	AntiEpic->OnClicked.AddDynamic(this, &UGameOptionWidget::SetAntiEpic);
	// Texture Qualtiy
	TextureLow->OnClicked.AddDynamic(this, &UGameOptionWidget::SetTextureLow);
	TextureMedium->OnClicked.AddDynamic(this, &UGameOptionWidget::SetTextureMedium);
	TextureHigh->OnClicked.AddDynamic(this, &UGameOptionWidget::SetTextureHigh);
	TextureEpic->OnClicked.AddDynamic(this, &UGameOptionWidget::SetTextureEpic);
	// Shadow Qualtiy
	ShadowLow->OnClicked.AddDynamic(this, &UGameOptionWidget::SetShadowLow);
	ShadowMedium->OnClicked.AddDynamic(this, &UGameOptionWidget::SetShadowMedium);
	ShadowHigh->OnClicked.AddDynamic(this, &UGameOptionWidget::SetShadowHigh);
	ShadowEpic->OnClicked.AddDynamic(this, &UGameOptionWidget::SetShadowEpic);

}

void UGameOptionWidget::SetFullScreen()
{
	if (setting)
	{
		setting->SetFullscreenMode(EWindowMode::Fullscreen);
		setting->ApplySettings(true);
		FullScreenBtn->SetIsEnabled(false);
		WindowBtn->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetWindowScreen()
{
	if (setting)
	{
		setting->SetFullscreenMode(EWindowMode::Windowed);
		setting->ApplySettings(true);
		FullScreenBtn->SetIsEnabled(true);
		WindowBtn->SetIsEnabled(false);
	}
}

void UGameOptionWidget::Set30FPS()
{
	if (setting)
	{
		setting->SetFrameRateLimit(30.f);
		setting->ApplySettings(true);
		FPS30Btn->SetIsEnabled(false);
		FPS60Btn->SetIsEnabled(true);
		FPS120Btn->SetIsEnabled(true);
		FPSBtn->SetIsEnabled(true);
	}
}

void UGameOptionWidget::Set60FPS()
{
	if (setting)
	{
		setting->SetFrameRateLimit(60.f);
		setting->ApplySettings(true);
		FPS30Btn->SetIsEnabled(true);
		FPS60Btn->SetIsEnabled(false);
		FPS120Btn->SetIsEnabled(true);
		FPSBtn->SetIsEnabled(true);
	}
}

void UGameOptionWidget::Set120FPS()
{
	if (setting)
	{
		setting->SetFrameRateLimit(120.f);
		setting->ApplySettings(true);
		FPS30Btn->SetIsEnabled(true);
		FPS60Btn->SetIsEnabled(true);
		FPS120Btn->SetIsEnabled(false);
		FPSBtn->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetUnlimitFPS()
{
	if (setting)
	{
		setting->SetFrameRateLimit(0.f);
		setting->ApplySettings(true);
		FPS30Btn->SetIsEnabled(true);
		FPS60Btn->SetIsEnabled(true);
		FPS120Btn->SetIsEnabled(true);
		FPSBtn->SetIsEnabled(false);
	}
}

void UGameOptionWidget::SetViewMedium()
{
	if (setting)
	{
		setting->SetViewDistanceQuality(0);
		setting->ApplySettings(true);
		ViewMedium->SetIsEnabled(false);
		ViewNear->SetIsEnabled(true);
		ViewFar->SetIsEnabled(true);
		ViewEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetViewNear()
{
	if (setting)
	{
		setting->SetViewDistanceQuality(1);
		setting->ApplySettings(true);
		ViewMedium->SetIsEnabled(true);
		ViewNear->SetIsEnabled(false);
		ViewFar->SetIsEnabled(true);
		ViewEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetViewFar()
{
	if (setting)
	{
		setting->SetViewDistanceQuality(2);
		setting->ApplySettings(true);
		ViewMedium->SetIsEnabled(true);
		ViewNear->SetIsEnabled(true);
		ViewFar->SetIsEnabled(false);
		ViewEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetViewEpic()
{
	if (setting)
	{
		setting->SetViewDistanceQuality(3);
		setting->ApplySettings(true);
		ViewMedium->SetIsEnabled(true);
		ViewNear->SetIsEnabled(true);
		ViewFar->SetIsEnabled(true);
		ViewEpic->SetIsEnabled(false);
	}
}

void UGameOptionWidget::SetPostLow()
{
	if (setting)
	{
		setting->SetPostProcessingQuality(0);
		setting->ApplySettings(true);
		PostLow->SetIsEnabled(false);
		PostMedium->SetIsEnabled(true);
		PostHigh->SetIsEnabled(true);
		PostEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetPostMedium()
{
	if (setting)
	{
		setting->SetPostProcessingQuality(1);
		setting->ApplySettings(true);
		PostLow->SetIsEnabled(true);
		PostMedium->SetIsEnabled(false);
		PostHigh->SetIsEnabled(true);
		PostEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetPostHigh()
{
	if (setting)
	{
		setting->SetPostProcessingQuality(2);
		setting->ApplySettings(true);
		PostLow->SetIsEnabled(true);
		PostMedium->SetIsEnabled(true);
		PostHigh->SetIsEnabled(false);
		PostEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetPostEpic()
{
	if (setting)
	{
		setting->SetPostProcessingQuality(3);
		setting->ApplySettings(true);
		PostLow->SetIsEnabled(true);
		PostMedium->SetIsEnabled(true);
		PostHigh->SetIsEnabled(true);
		PostEpic->SetIsEnabled(false);
	}
}

void UGameOptionWidget::SetAntiLow()
{
	if (setting)
	{
		setting->SetAntiAliasingQuality(0);
		setting->ApplySettings(true);
		AntiLow->SetIsEnabled(false);
		AntiMedium->SetIsEnabled(true);
		AntiHigh->SetIsEnabled(true);
		AntiEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetAntiMedium()
{
	if (setting)
	{
		setting->SetAntiAliasingQuality(1);
		setting->ApplySettings(true);
		AntiLow->SetIsEnabled(true);
		AntiMedium->SetIsEnabled(false);
		AntiHigh->SetIsEnabled(true);
		AntiEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetAntiHigh()
{
	if (setting)
	{
		setting->SetAntiAliasingQuality(2);
		setting->ApplySettings(true);
		AntiLow->SetIsEnabled(true);
		AntiMedium->SetIsEnabled(true);
		AntiHigh->SetIsEnabled(false);
		AntiEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetAntiEpic()
{
	if (setting)
	{
		setting->SetAntiAliasingQuality(3);
		setting->ApplySettings(true);
		AntiLow->SetIsEnabled(true);
		AntiMedium->SetIsEnabled(true);
		AntiHigh->SetIsEnabled(true);
		AntiEpic->SetIsEnabled(false);
	}
}

void UGameOptionWidget::SetTextureLow()
{
	if (setting)
	{
		setting->SetTextureQuality(0);
		setting->ApplySettings(true);
		TextureLow->SetIsEnabled(false);
		TextureMedium->SetIsEnabled(true);
		TextureHigh->SetIsEnabled(true);
		TextureEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetTextureMedium()
{
	if (setting)
	{
		setting->SetTextureQuality(1);
		setting->ApplySettings(true);
		TextureLow->SetIsEnabled(true);
		TextureMedium->SetIsEnabled(false);
		TextureHigh->SetIsEnabled(true);
		TextureEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetTextureHigh()
{
	if (setting)
	{
		setting->SetTextureQuality(2);
		setting->ApplySettings(true);
		TextureLow->SetIsEnabled(true);
		TextureMedium->SetIsEnabled(true);
		TextureHigh->SetIsEnabled(false);
		TextureEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetTextureEpic()
{
	if (setting)
	{
		setting->SetTextureQuality(3);
		setting->ApplySettings(true);
		TextureLow->SetIsEnabled(true);
		TextureMedium->SetIsEnabled(true);
		TextureHigh->SetIsEnabled(true);
		TextureEpic->SetIsEnabled(false);
	}
}

void UGameOptionWidget::SetShadowLow()
{
	if (setting)
	{
		setting->SetShadowQuality(0);
		setting->ApplySettings(true);
		ShadowLow->SetIsEnabled(false);
		ShadowMedium->SetIsEnabled(true);
		ShadowHigh->SetIsEnabled(true);
		ShadowEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetShadowMedium()
{
	if (setting)
	{
		setting->SetShadowQuality(1);
		setting->ApplySettings(true);
		ShadowLow->SetIsEnabled(true);
		ShadowMedium->SetIsEnabled(false);
		ShadowHigh->SetIsEnabled(true);
		ShadowEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetShadowHigh()
{
	if (setting)
	{
		setting->SetShadowQuality(2);
		setting->ApplySettings(true);
		ShadowLow->SetIsEnabled(true);
		ShadowMedium->SetIsEnabled(true);
		ShadowHigh->SetIsEnabled(false);
		ShadowEpic->SetIsEnabled(true);
	}
}

void UGameOptionWidget::SetShadowEpic()
{
	if (setting)
	{
		setting->SetShadowQuality(3);
		setting->ApplySettings(true);
		ShadowLow->SetIsEnabled(true);
		ShadowMedium->SetIsEnabled(true);
		ShadowHigh->SetIsEnabled(true);
		ShadowEpic->SetIsEnabled(false);
	}
}
