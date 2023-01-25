// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "FindAppleAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FonActionCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FonActionHitCheckDelegate);

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
	UPROPERTY(VisibleAnywhere, Category = Equip)
	UStaticMeshComponent* Sword;

	FonActionCheckDelegate OnActionMon;
	FonActionHitCheckDelegate OnActHitMon;

private:
	UFUNCTION()
	void AnimNotify_HitCheck();

	UFUNCTION()
	void AnimNotify_HitEnd();

	FName GetActionMontageSecName(int32 Section);


};
