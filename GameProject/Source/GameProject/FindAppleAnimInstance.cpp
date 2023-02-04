
// Fill out your copyright notice in the Description page of Project Settings.


#include "FindAppleAnimInstance.h"
#include "FindAppleCharacter.h"

UFindAppleAnimInstance::UFindAppleAnimInstance()
{
	UE_LOG(LogTemp, Error, TEXT("Animinstance start"));
	Speed = 0.f;
	OnAir = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ACTION_MON
	(TEXT("/Script/Engine.AnimMontage'/Game/Characters/Hero/ActionMontage.ActionMontage'"));
	if (ACTION_MON.Succeeded()) {
		ActionMontage = ACTION_MON.Object;
	}

}

void UFindAppleAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;

	//주인공 speed갱신
	Speed = Pawn->GetVelocity().Size();

	//공중인지아닌지갱신
	auto hero = Cast<AFindAppleCharacter>(Pawn);
	if (hero) {
		OnAir = hero->GetCharacterMovement()->IsFalling();

	}
}

void UFindAppleAnimInstance::PlayActionMontage()
{

	Montage_Play(ActionMontage, 1.f);
	Montage_JumpToSection(TEXT("PlantSeed"));

}

void UFindAppleAnimInstance::AnimNotify_HitStart()
{

	HitCheckStart.ExecuteIfBound();

}

void UFindAppleAnimInstance::AnimNotify_HitEnd()
{
	HitCheckEnd.ExecuteIfBound();


}

void UFindAppleAnimInstance::AnimNotify_Release()
{
	RelaseSeed.ExecuteIfBound();

}

void UFindAppleAnimInstance::AnimNotify_Grab()
{
	GrabSeed.ExecuteIfBound();
}


