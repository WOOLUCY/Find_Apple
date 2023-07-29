// Fill out your copyright notice in the Description page of Project Settings.


#include "Stone.h"
#include "../Inventory/DropedItem.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "../FindAppleCharacter.h"

// Sets default values
AStone::AStone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TotalDamage = 0;
	MaxDamage = 30;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));
	RespawnTime = 30;

	RootComponent = mesh;
	light->SetupAttachment(RootComponent);
	light->AddRelativeLocation(FVector(0, 0, 94.f));
	light->SetIntensity(600.f);
}

void AStone::RespawnStone()
{
	TotalDamage = 0;
	mesh->SetVisibility(true);
	light->SetVisibility(true);
	

}

float AStone::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvnet, AController* EvnetInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("djkfl;sdfjklsdf"));
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvnet, EvnetInstigator, DamageCauser);
	static bool once = true;

	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr) {
		auto hero = UGameplayStatics::GetPlayerCharacter(TheWorld, 0);

		if (Cast<AFindAppleCharacter>(hero)) {

			if (TotalDamage > MaxDamage) {
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Wow"));
				mesh->SetVisibility(false);
				light->SetVisibility(false);

				FVector PivotWorld = GetActorLocation();
				if (once) {
					ADropedItem* DropedActor = GetWorld()->SpawnActor<ADropedItem>(PivotWorld + FVector(0, 0, 50.f), FRotator::ZeroRotator);
					DropedActor->ItemFresh(name);
					once = false;
				}

				FTimerHandle Timer;
				GetWorldTimerManager().SetTimer(Timer, this, &AStone::RespawnStone, RespawnTime);

			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("???Wow"));

				TotalDamage += FinalDamage;
				once = true;

			}

		}

	}
	return 0.f;

}

// Called when the game starts or when spawned
void AStone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

