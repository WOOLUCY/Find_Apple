// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FindApplePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API AFindApplePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* pawn) override;

	UFUNCTION()
	void changeMouse();

protected:
	virtual void SetupInputComponent() override;
	// Called when the game starts or when spawned

};
