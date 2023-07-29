// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Components/WidgetComponent.h"

#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AInGameHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
		void UpdateHeartCount();

	UFUNCTION()
		void UpdateHunger();

	UFUNCTION()
		void UpdateToolImage();

	UFUNCTION()
		void UpdateFishingProcess();


	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> HPWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> ToolWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> TimeWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> HungerWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> FishWidgetClass;

private:
	UPROPERTY()
	class UHPWidget* HPWidget;
	UPROPERTY()
	class UToolWidget* ToolWidget;
	UPROPERTY()
	class UTimeWidget* TimeWidget;
	UPROPERTY()
	class UHungerWidget* HungerWidget;
	UPROPERTY()
	class UFishWidget* FishWidget;
};
