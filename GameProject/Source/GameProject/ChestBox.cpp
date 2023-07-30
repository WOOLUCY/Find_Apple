// Fill out your copyright notice in the Description page of Project Settings.


#include "ChestBox.h"
#include "Inventory/DropedItem.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "FindAppleCharacter.h"

// Sets default values
AChestBox::AChestBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TotalDamage = 0;
	MaxDamage = 10;
	RespawnTime = 30;
	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));


	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_CHEST
	(TEXT("/Script/Engine.StaticMesh'/Game/Woo/Monster/Chest/chest_default.chest_default'"));
	if (SM_CHEST.Succeeded()) {
		//ChestMehs = SM_CHEST.Object;
		ChestMesh->SetStaticMesh(SM_CHEST.Object);
	}
	RootComponent = ChestMesh;



}

void AChestBox::RespawnBox()
{

	TotalDamage = 0.f;
	ChestMesh->SetVisibility(true);
	ChestMesh->SetCollisionProfileName("BlockAll");



}

float AChestBox::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvnet, AController* EvnetInstigator, AActor* DamageCauser)
{

	UE_LOG(LogTemp, Warning, TEXT("TakeDamate ChestBox"));
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvnet, EvnetInstigator, DamageCauser);
	static bool once = true;

	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr) {
		auto hero = UGameplayStatics::GetPlayerCharacter(TheWorld, 0);

		if (Cast<AFindAppleCharacter>(hero)) {

			if (TotalDamage > MaxDamage) {
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Wow"));
				ChestMesh->SetVisibility(false);
	
				FVector PivotWorld = GetActorLocation();
				if (once) {
					ADropedItem* DropedActor = GetWorld()->SpawnActor<ADropedItem>(PivotWorld + FVector(0, 0, 70.f), FRotator::ZeroRotator);
					DropedActor->ItemFresh(ItemName);
					once = false;
					ChestMesh->SetCollisionProfileName("NoCollision");
				}

				FTimerHandle Timer;
				GetWorldTimerManager().SetTimer(Timer, this, &AChestBox::RespawnBox, RespawnTime);

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
void AChestBox::BeginPlay()
{
	Super::BeginPlay();
	int RandonNumber = FMath::RandRange(0, 3);
		// 랜덤으로 아이템 스폰되게 해야함
	// 돌종류로 해야할듯 
	//ItemName = 

	switch (RandonNumber)
	{
	case 0:
		ItemName = "Rubby";
		break;
	case 1:
		ItemName = "iron";

		break;
	case 2:
		ItemName = "gold";

		break;
	case 3:
		ItemName = "Rubby";
		break;
	default:
		break;
	}
}

// Called every frame
void AChestBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

