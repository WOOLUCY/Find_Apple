// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FindAppleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFindAppleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEPROJECT_API IFindAppleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/* Dialogue Activate */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dialogue")
	void OnActivate();

	/* Item Pick up Interface */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory")
	void PicUpItem();
};
