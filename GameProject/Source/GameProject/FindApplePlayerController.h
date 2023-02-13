// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlantWidget.h"
#include "FindApplePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API AFindApplePlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	AFindApplePlayerController();


	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* pawn) override;
	virtual void BeginPlay() override;


	void ShowPlantWidget();
	void HiddenPlantWidget();

protected:
	virtual void SetupInputComponent() override;
	// Called when the game starts or when spawned

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UPlantWidget> PlantWidgetClass;

private:
	UPROPERTY()
		class UPlantWidget* PlantWdiget;

};
