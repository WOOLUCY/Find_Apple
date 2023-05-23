
// Fill out your copyright notice in the Description page of Project Settings.


#include "FindAppleAnimInstance.h"
#include "FindApplePlayerController.h"
#include "Engine/EngineTypes.h"
#include "FindAppleCharacter.h"

UFindAppleAnimInstance::UFindAppleAnimInstance()
{
	//UE_LOG(LogTemp, Error, TEXT("Animinstance start"));
	Speed = 0.f;
	OnAir = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ACTION_MON
	(TEXT("/Script/Engine.AnimMontage'/Game/Characters/Hero/ActionMontage.ActionMontage'"));
	if (ACTION_MON.Succeeded()) {
		ActionMontage = ACTION_MON.Object;
	}


	static ConstructorHelpers::FObjectFinder<UAnimMontage> PLANT_MON
	(TEXT("/Script/Engine.AnimMontage'/Game/Characters/Hero/PlantMontage.PlantMontage'"));
	if (PLANT_MON.Succeeded()) {
		PlantMontage = PLANT_MON.Object;
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
	static float PlayLength = PlantMontage->GetPlayLength() / (PlaySpeed * 1.5f);

	if (OffInput()) {
		Montage_Play(ActionMontage, PlaySpeed);
		UWorld* World = GetWorld();
		if (World){
			UE_LOG(LogTemp, Warning, TEXT("OnInpnut!!!!!!!!????????!"));

			FTimerManager& TimerManager = World->GetTimerManager();

			TimerManager.SetTimer(TimerHandle, this, &UFindAppleAnimInstance::OnInput, 0.2f, false);
		}

	}
	// 애니메이션이 끝나면 입력 활성화

}

void UFindAppleAnimInstance::PlayPlantMontage()
{
	static float PlayLength = PlantMontage->GetPlayLength()/ (PlaySpeed * 1.5f);

	if (OffInput()) {
		Montage_Play(PlantMontage, PlaySpeed);

	
		UWorld* World = GetWorld();
		if (World) {

			FTimerManager& TimerManager = World->GetTimerManager();

			TimerManager.SetTimer(TimerHandle, this, &UFindAppleAnimInstance::OnInput, PlayLength, false);
		}
	}


}

bool UFindAppleAnimInstance::OffInput()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AFindApplePlayerController* Mycontol = Cast<AFindApplePlayerController>(PlayerController);
	if (Mycontol != nullptr) {
		Mycontol->GetPawn()->DisableInput(Mycontol);
		return true;
	}
	return false;

}

void UFindAppleAnimInstance::OnInput()
{
	UE_LOG(LogTemp, Warning, TEXT("OnInpnut!!!!!!!!!"));
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AFindApplePlayerController* Mycontol = Cast<AFindApplePlayerController>(PlayerController);
	if (Mycontol != nullptr) {
		Mycontol->GetPawn()->EnableInput(Mycontol);
	}
}

void UFindAppleAnimInstance::AnimNotify_HitStart()
{

	HitCheckStart.ExecuteIfBound();

}

void UFindAppleAnimInstance::AnimNotify_HitEnd()
{
	HitCheckEnd.ExecuteIfBound();


}


