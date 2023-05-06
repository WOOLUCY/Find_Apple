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

	// »ç¸Á Ã³¸®
	//if (Health <= 0.f)
	//{
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		GetMesh()->SetMaterial(i, DissolveMaterial);
	//	}

	//	//GetMovementComponent()->StopMovementImmediately();
	//	GetMesh()->Stop();
	//	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//	FTimerHandle TimerHandle;
	//	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
	//		{
	//			Destroy();
	//		}, 0.8f, false);

	//	//Destroy();
	//}

}

// Called to bind functionality to input
void AChestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AChestCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

