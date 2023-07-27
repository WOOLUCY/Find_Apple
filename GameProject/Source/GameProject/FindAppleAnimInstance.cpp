
// Fill out your copyright notice in the Description page of Project Settings.


#include "FindAppleAnimInstance.h"
#include "FindApplePlayerController.h"
#include "Engine/EngineTypes.h"
#include "FindAppleCharacter.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Sound/SoundCue.h"

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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> GRAB_MON
	(TEXT("/Script/Engine.AnimMontage'/Game/Characters/Hero/GrabMontage.GrabMontage'"));
	if (GRAB_MON.Succeeded()) {
		GrabMontage = GRAB_MON.Object;
	}


	static ConstructorHelpers::FObjectFinder<USoundCue> CONCRETE_CUE
	(TEXT("/Script/Engine.SoundCue'/Game/Semin/Sound/FootStep/Concrete_Sound_Cue.Concrete_Sound_Cue'"));
	if (CONCRETE_CUE.Succeeded()) {
		ConcreteSoundCue = CONCRETE_CUE.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> GRASS_CUE
	(TEXT("/Script/Engine.SoundCue'/Game/Semin/Sound/FootStep/Grass_Sound_Cue.Grass_Sound_Cue'"));
	if (GRASS_CUE.Succeeded()) {
		GrassSoundCue = GRASS_CUE.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> WOOD_CUE
	(TEXT("/Script/Engine.SoundCue'/Game/Semin/Sound/FootStep/Wood_Sound_Cue.Wood_Sound_Cue'"));
	if (WOOD_CUE.Succeeded()) {
		WoodSoundCue = WOOD_CUE.Object;
	}

	//Grab Music Sound
	static ConstructorHelpers::FObjectFinder<USoundWave> GrabSoundCue(TEXT("/Script/Engine.SoundWave'/Game/Semin/Sound/Grab.Grab'"));
	GrabAudioCue = GrabSoundCue.Object;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PropellerAudioComp"));
	AudioComponent->bAutoActivate = false;
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

void UFindAppleAnimInstance::PlayGrabItemMontage()
{
	static float PlayLength = GrabMontage->GetPlayLength() / (PlaySpeed * 2.f);

	if (OffInput()) {
		Montage_Play(GrabMontage, PlaySpeed);
		UWorld* World = GetWorld();

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->GetCharacter()->GetCharacterMovement()->SetActive(false);

		if (World) {
			FTimerManager& TimerManager = World->GetTimerManager();

			TimerManager.SetTimer(TimerHandle, this, &UFindAppleAnimInstance::OnInput, 0.2f, false);

			

			AudioComponent->SetSound(GrabAudioCue);
			AudioComponent->Play();
		}

	}
	// 애니메이션이 끝나면 입력 활성화
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

void UFindAppleAnimInstance::AnimNotify_FootStep()
{
	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FHitResult HitResult;
	FCollisionResponseParams ResponseParams;
	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	FActorSpawnParameters SpawnParams;
	QueryParams.bReturnPhysicalMaterial = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector StartTrace = CharacterActor->GetActorLocation();
	FVector EndTrace = CharacterActor->GetActorLocation() - FVector(0, 0, 150);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility, QueryParams, ResponseParams))
	{
		if (AActor* HitActor = Cast<AActor> (HitResult.GetActor()))
		{
			switch (HitResult.PhysMaterial->SurfaceType) 
			{
			case SurfaceType1:
				AudioComponent->SetSound(WoodSoundCue);
				AudioComponent->Play();
				break;
			case SurfaceType2:
				AudioComponent->SetSound(GrassSoundCue);
				AudioComponent->Play();
				break;
			case SurfaceType3:
				AudioComponent->SetSound(ConcreteSoundCue);
				AudioComponent->Play();
				break;
			}
		}


	}

}


