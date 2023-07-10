// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"
#include "../Inventory/DropedItem.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../FindAppleCharacter.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"
#include "HealthBarWidget.h"
#include "Components/WidgetComponent.h"
//#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ASlimeCharacter::ASlimeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Animation */
	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	//static ConstructorHelpers::FClassFinder<UAnimInstance> SlimeAnimBP
	//(TEXT("/Script/Engine.AnimBlueprint'/Game/Monsters/Slime/SlimeAnimBP.SlimeAnimBP_C'"));

	//if (SlimeAnimBP.Succeeded()) {
	//	GetMesh()->SetAnimInstanceClass(SlimeAnimBP.Class);
	//}


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

	FString DissolveName = "/Script/Engine.MaterialInstanceConstant'/Game/Woo/Monster/Slime/MI_Dissolve.MI_Dissolve'";
	ConstructorHelpers::FObjectFinder<UMaterialInterface> DissolveMaterialAsset(*DissolveName);
	DissolveMaterial = DissolveMaterialAsset.Object;

	//sound
	static ConstructorHelpers::FObjectFinder<USoundWave> propellerCue(TEXT("/Script/Engine.SoundWave'/Game/Semin/Sound/SlimeHit.SlimeHit'"));
	HitAudioCue = propellerCue.Object;
	HitAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PropellerAudioComp"));
	HitAudioComponent->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<USoundWave> propellerCue2(TEXT("/Script/Engine.SoundWave'/Game/Semin/Sound/MonsterDeath.MonsterDeath'"));
	DeadAudioCue = propellerCue2.Object;


	//set health bar widget
	HealthBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));

	ConstructorHelpers::FClassFinder<UHealthBarWidget>  HealthBarWidgetObject(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Woo/AI/WBP_HealthBar.WBP_HealthBar_C'"));
	if (HealthBarWidgetObject.Succeeded())
	{
		HealthBarWidgetClass = HealthBarWidgetObject.Class;
		HealthBarWidgetComp->SetWidgetClass(HealthBarWidgetClass);
	}

	HealthBarWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	HealthBarWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
	HealthBarWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidgetComp->SetHiddenInGame(true);
	HealthBarWidgetComp->SetDrawSize(FVector2D(100, 8));
}

void ASlimeCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HitAudioCue->IsValidLowLevelFast()) {
		HitAudioComponent->SetSound(HitAudioCue);
	}
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

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(PlayerPawn);
	// 플레이어와 거리가 1000 이하일 때만 체력바 표시
	if (GetDistanceTo(MyCharacter) <= 1000) 
	{
		HealthBarWidgetComp->SetHiddenInGame(false);
	}
	else
	{
		HealthBarWidgetComp->SetHiddenInGame(true);
	}
	
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
		if (deadSound == false) 
		{
			UGameplayStatics::PlaySoundAtLocation(this, DeadAudioCue, GetActorLocation());
			deadSound = true;
		}

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
				ADropedItem* DropedActor;

				if (IsDead == false) 
				{
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
void ASlimeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ASlimeCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
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

		UHealthBarWidget* HealthWidgetUI = Cast<UHealthBarWidget>(HealthBarWidgetComp->GetUserWidgetObject());
		HealthWidgetUI->SetHealthBarProgress(MaxHealth, Health);

		UE_LOG(LogClass, Warning, TEXT("Slime Is Attacked"));
		UE_LOG(LogClass, Warning, TEXT("Slime Current HP: %f"), Health);

		IsAttacked = false;
	}
	else
	{
		Health -= 20.f;

		UHealthBarWidget* HealthWidgetUI = Cast<UHealthBarWidget>(HealthBarWidgetComp->GetUserWidgetObject());
		HealthWidgetUI->SetHealthBarProgress(MaxHealth, Health);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		   {

			   UE_LOG(LogClass, Warning, TEXT("Slime Is Attacked"));
			   UE_LOG(LogClass, Warning, TEXT("Slime Current HP: %f"), Health);

			   IsAttacked = false;
		   }, 0.5f, false);
	}

	return Damage;
}


