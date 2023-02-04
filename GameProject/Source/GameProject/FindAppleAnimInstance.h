// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"

#include "FindAppleAnimInstance.generated.h"


DECLARE_DELEGATE(FonActionCheckDelegate);

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

	//¸ùÅ¸ÁÖ 
	void PlayActionMontage();


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Move, Meta = (AllowPrivateAccess = true))
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Move, Meta = (AllowPrivateAccess = true))
		bool OnAir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ActionMontage;



public:
	FonActionCheckDelegate HitCheckStart; 
	FonActionCheckDelegate HitCheckEnd;
	FonActionCheckDelegate GrabSeed;
	FonActionCheckDelegate RelaseSeed;

private:
	UFUNCTION()
	void AnimNotify_HitStart();

	UFUNCTION()
	void AnimNotify_HitEnd();


	UFUNCTION()
		void AnimNotify_Release();

	UFUNCTION()
		void AnimNotify_Grab();



};
