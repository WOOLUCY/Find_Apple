// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DoOnce.generated.h"

USTRUCT(BlueprintType)
struct FDoOnce
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool bDoOnce;

	FORCEINLINE FDoOnce();
	explicit FORCEINLINE FDoOnce(bool bStartClosed);

	FORCEINLINE void Reset() { bDoOnce = true; }

	FORCEINLINE bool Execute()
	{
		if(bDoOnce)
		{
			bDoOnce = false;
			return true;
		}
		return false;
	}

};

FORCEINLINE FDoOnce::FDoOnce() : bDoOnce(false)
{}

FORCEINLINE FDoOnce::FDoOnce(const bool bStartClosed) : bDoOnce(!bStartClosed)
{}