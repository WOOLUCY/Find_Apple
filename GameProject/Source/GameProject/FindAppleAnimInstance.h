// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "FindAppleAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class GAMEPROJECT_API UFindAppleAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFindAppleAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//��Ÿ�� 
	void PlayActionMontage();


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Move, Meta = (AllowPrivateAccess = true))
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Move, Meta = (AllowPrivateAccess = true))
		bool OnAir;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ActionMontage;



};
