// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

// Sets default values
ASlimeCharacter::ASlimeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Slime Material Load */
	FString Material01Name = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Slime/MI_Slime01.MI_Slime01'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material01Asset(*Material01Name);
	Material01 = Material01Asset.Object;

	FString Material02Name = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Slime/MI_Slime02.MI_Slime02'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material02Asset(*Material02Name);
	Material02 = Material02Asset.Object;

	FString Material03Name = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Slime/MI_Slime03.MI_Slime03'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material03Asset(*Material03Name);
	Material03 = Material03Asset.Object;

	FString Material04Name = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Slime/MI_Slime04.MI_Slime04'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material04Asset(*Material04Name);
	Material04 = Material04Asset.Object;

	FString Material05Name = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Slime/MI_Slime05.MI_Slime05'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material05Asset(*Material05Name);
	Material05 = Material05Asset.Object;

	
}

// Called when the game starts or when spawned
void ASlimeCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ASlimeCharacter::Tick(float DeltaTime)
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
	//else if (Health <= 0.f)
	//{
	//	GetMesh()->Stop();
	//	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//	FString DeadAnimAssetName = "/Script/Engine.AnimSequence'/Game/Monsters/Slime/Damged.Damged'";
	//	ConstructorHelpers::FObjectFinder<UAnimationAsset> DeadAnimationAsset(*DeadAnimAssetName);
	//	GetMesh()->PlayAnimation(DeadAnimationAsset.Object, false);

	//	FTimerHandle WaitHandle;
	//	float WaitTime = 3.f;

	//	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
	//		{
	//			GetWorld()->GetTimerManager().ClearTimer(WaitHandle);
	//		}), WaitTime, false);

	//	Destroy();
	//}

}

// Called to bind functionality to input
void ASlimeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ASlimeCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	IsAttacked = true;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			Health -= 20.f;

			UE_LOG(LogClass, Warning, TEXT("Slime Is Attacked"));
			UE_LOG(LogClass, Warning, TEXT("Slime Current HP: %f"), Health);

			IsAttacked = false;
		}, 0.5f, false);

	return Damage;
}

