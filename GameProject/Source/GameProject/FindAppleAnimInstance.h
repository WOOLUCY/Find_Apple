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
	void PlayPlantMontage();
	void PlayGrabItemMontage();



private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Move, Meta = (AllowPrivateAccess = true))
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Move, Meta = (AllowPrivateAccess = true))
		bool OnAir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ActionMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* PlantMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Action, Meta = (AllowPrivateAccess = true))
		UAnimMontage* GrabMontage;

	FTimerHandle TimerHandle;

	float PlaySpeed = 2.f;



public:
	FonActionCheckDelegate HitCheckStart; 
	FonActionCheckDelegate HitCheckEnd;

	bool  OffInput();
	void  OnInput();

	UPROPERTY()
	class USoundCue* WoodSoundCue;
	UPROPERTY()
	class USoundCue* GrassSoundCue;
	UPROPERTY()
	class USoundCue* ConcreteSoundCue;

	//Pick sound
	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundWave* GrabAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundWave* WeildAudioCue;

	UPROPERTY()
	class UAudioComponent* AudioComponent;

	UPROPERTY()
	class UAudioComponent* InteractAudioComponent;

private:
	UFUNCTION()
	void AnimNotify_HitSound();

	UFUNCTION()
	void AnimNotify_HitStart();

	UFUNCTION()
	void AnimNotify_HitEnd();
	
	UFUNCTION()
	void AnimNotify_FootStep();

};
