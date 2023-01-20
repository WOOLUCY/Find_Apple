// Fill out your copyright notice in the Description page of Project Settings.


#include "FindAppleAnimInstance.h"
#include "FindAppleCharacter.h"

UFindAppleAnimInstance::UFindAppleAnimInstance()
{
	Speed = 0.f;
	Angle = 0.f;
	OnAir = false;
}

void UFindAppleAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;

	//주인공 speed갱신
	Speed = Pawn->GetVelocity().Size();
	
	auto hero = Cast<AFindAppleCharacter>(Pawn);
	if (hero) {
		OnAir = hero->GetCharacterMovement()->IsFalling();

	}
	





}
