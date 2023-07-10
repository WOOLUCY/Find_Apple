// Fill out your copyright notice in the Description page of Project Settings.


#include "NepenthesCharacter.h"
#include "../Inventory/DropedItem.h"
#include "Kismet/GameplayStatics.h"
#include "../FindAppleCharacter.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"

// Sets default values
ANepenthesCharacter::ANepenthesCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString DissolveName = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Nepenthes/MI_Dissolve.MI_Dissolve'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> DissolveMaterialAsset(*DissolveName);
	DissolveMaterial = DissolveMaterialAsset.Object;

	//sound
	static ConstructorHelpers::FObjectFinder<USoundWave> propellerCue(TEXT("/Script/Engine.SoundWave'/Game/Semin/Sound/Monster_attack.Monster_attack'"));
	HitAudioCue = propellerCue.Object;
	HitAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PropellerAudioComp"));
	HitAudioComponent->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<USoundWave> propellerCue2(TEXT("/Script/Engine.SoundWave'/Game/Semin/Sound/MonsterDeath.MonsterDeath'"));
	DeadAudioCue = propellerCue2.Object;
}

void ANepenthesCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HitAudioCue->IsValidLowLevelFast()) {
		HitAudioComponent->SetSound(HitAudioCue);
	}
}

// Called when the game starts or when spawned
void ANepenthesCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANepenthesCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: Destroy Slime
	if (Health <= 0.f)
	{
		if (deadSound == false)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DeadAudioCue, GetActorLocation());
			deadSound = true;
		}

		GetMesh()->SetMaterial(0, DissolveMaterial);
		

		//GetMovementComponent()->StopMovementImmediately();
		GetMesh()->Stop();
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				if (IsDead == false)
				{
					ADropedItem* DropedActor;

					DropedActor = GetWorld()->SpawnActor<ADropedItem>(ADropedItem::StaticClass(), GetActorLocation(), GetActorRotation());
					DropedActor->CollisionMesh->SetBoxExtent(FVector(30.f, 30.f, 30.f));
					DropedActor->CollisionMesh->SetWorldLocation(DropedActor->MyBox->GetComponentLocation());
					DropedActor->ItemFresh(FName("Seed"));
					IsDead = true;

					APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
					AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(PlayerPawn);

					MyCharacter->countOfMonstersAggro -= 1;
				}

				Destroy();
			}, 1.2f, false);

		//Destroy();
	}

}

// Called to bind functionality to input
void ANepenthesCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ANepenthesCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (Health <= 0.f)
		return	0.f;

	HitAudioComponent->Play();

	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	IsAttacked = true;

	FTimerHandle TimerHandle;
	if (Health <= 20.f)
	{
		Health -= 20.f;

		UE_LOG(LogClass, Warning, TEXT("Slime Is Attacked"));
		UE_LOG(LogClass, Warning, TEXT("Slime Current HP: %f"), Health);

		IsAttacked = false;
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				Health -= 20.f;

				UE_LOG(LogClass, Warning, TEXT("Slime Is Attacked"));
				UE_LOG(LogClass, Warning, TEXT("Slime Current HP: %f"), Health);

				IsAttacked = false;
			}, 0.5f, false);
	}



	return Damage;
}

