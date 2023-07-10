// Fill out your copyright notice in the Description page of Project Settings.


#include "NepenthesCharacter.h"
#include "../Inventory/DropedItem.h"
#include "Kismet/GameplayStatics.h"
#include "../FindAppleCharacter.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"
#include "HealthBarWidget.h"
#include "Components/WidgetComponent.h"

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


	//set health bar widget
	HealthBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));

	ConstructorHelpers::FClassFinder<UHealthBarWidget>  HealthBarWidgetObject(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Woo/AI/WBP_HealthBar.WBP_HealthBar_C'"));
	if (HealthBarWidgetObject.Succeeded())
	{
		HealthBarWidgetClass = HealthBarWidgetObject.Class;
		HealthBarWidgetComp->SetWidgetClass(HealthBarWidgetClass);
	}

	HealthBarWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	HealthBarWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 40.f));
	HealthBarWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidgetComp->SetHiddenInGame(true);
	HealthBarWidgetComp->SetDrawSize(FVector2D(100, 8));
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