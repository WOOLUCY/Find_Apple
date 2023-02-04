// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "QuestNPCAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UQuestNPCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UQuestNPCAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
