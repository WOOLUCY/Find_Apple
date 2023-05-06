// Fill out your copyright notice in the Description page of Project Settings.


#include "ChestCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

// Sets default values
AChestCharacter::AChestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString DissolveName = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Slime/MI_Dissolve.MI_Dissolve'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> DissolveMaterialAsset(*DissolveName);
	DissolveMaterial = DissolveMaterialAsset.Object;
}

// Called when the game starts or when spawned
void AChestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: Destroy Slime
	if (Health <= 0.f)
	{

		//GetMovementComponent()->StopMovementImmediately();
		GetMesh()->Stop();
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				Destroy();
			}, 0.8f, false);

		//Destroy();
	}
}

// Called to bind functionality to input
void AChestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AChestCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (Health <= 0.f)
		return	0.f;

	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	IsAttacked = true;

	FTimerHandle TimerHandle;
	if (Health <= 20.f)
	{
		Health -= 20.f;

		UE_LOG(LogClass, Warning, TEXT("Chest Is Attacked"));
		UE_LOG(LogClass, Warning, TEXT("Chest Current HP: %f"), Health);

		IsAttacked = false;
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				Health -= 20.f;

				UE_LOG(LogClass, Warning, TEXT("Chest Is Attacked"));
				UE_LOG(LogClass, Warning, TEXT("Chest Current HP: %f"), Health);

				IsAttacked = false;
			}, 0.5f, false);
	}

	return Damage;
}

