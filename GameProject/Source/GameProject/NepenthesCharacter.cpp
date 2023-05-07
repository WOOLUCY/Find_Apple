// Fill out your copyright notice in the Description page of Project Settings.


#include "NepenthesCharacter.h"

// Sets default values
ANepenthesCharacter::ANepenthesCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString Material01Name = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Nepenthes/MI_Nep01.MI_Nep01'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material01Asset(*Material01Name);
	Material01 = Material01Asset.Object;

	FString Material02Name = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Nepenthes/MI_Nep02.MI_Nep02'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material02Asset(*Material02Name);
	Material02 = Material02Asset.Object;

	FString Material03Name = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Nepenthes/MI_Nep03.MI_Nep03'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material03Asset(*Material03Name);
	Material03 = Material03Asset.Object;

	FString Material04Name = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Nepenthes/MI_Nep04.MI_Nep04'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material04Asset(*Material04Name);
	Material04 = Material04Asset.Object;

	FString Material05Name = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Nepenthes/MI_Nep05.MI_Nep05'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material05Asset(*Material05Name);
	Material05 = Material05Asset.Object;

	FString DissolveName = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Nepenthes/MI_Dissolve.MI_Dissolve'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> DissolveMaterialAsset(*DissolveName);
	DissolveMaterial = DissolveMaterialAsset.Object;
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
	if (Health == 100.f)
	{
		GetMesh()->SetMaterial(0, Material01);
	}

	else if (Health == 80.f)
	{
		GetMesh()->SetMaterial(0, Material02);
	}

	else if (Health == 60.f)
	{
		GetMesh()->SetMaterial(0, Material03);
	}

	else if (Health == 40.f)
	{
		GetMesh()->SetMaterial(0, Material04);
	}

	else if (Health == 20.f)
	{
		GetMesh()->SetMaterial(0, Material05);
	}

	// TODO: Destroy Slime
	else if (Health <= 0.f)
	{
		for (int i = 0; i < 4; ++i)
		{
			GetMesh()->SetMaterial(i, DissolveMaterial);
		}

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
void ANepenthesCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ANepenthesCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
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

