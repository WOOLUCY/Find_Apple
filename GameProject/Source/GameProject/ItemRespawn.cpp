// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemRespawn.h"
#include "Components/BoxComponent.h"
#include "Inventory/DropedItem.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AItemRespawn::AItemRespawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/* Collision Mesh */
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 64.f), FRotator(0.f, 0.f, 0.f));
	CollisionMesh->SetBoxExtent(FVector(64.f, 64.f, 64.f));
	CollisionMesh->SetupAttachment(GetRootComponent());
	CollisionMesh->SetHiddenInGame(true);

	SetRootComponent(CollisionMesh);

}

// Called when the game starts or when spawned
void AItemRespawn::BeginPlay()
{
	Super::BeginPlay();

	AdvanceTimer();

	/* Rock 일 때 높이 낮춤 */
	if (SpawnItemName == "rock")
	{
		CollisionMesh->SetBoxExtent(FVector(64.f, 64.f, 10.f));
	}

	/* 5 초마다 */
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AItemRespawn::AdvanceTimer, SecTimer, true);
}

// Called every frame
void AItemRespawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemRespawn::AdvanceTimer()
{
	CheckActors();
}

void AItemRespawn::CheckActors()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("CheckActors 5.f"));
	if (Actors.Num() > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Actors Num: %d"), Actors.Num());
		for (int i = 0; i < Actors.Num(); i++)
		{
			if ( !Actors[i].IsValid() )
			{
				//UE_LOG(LogTemp, Warning, TEXT("Remove Index Num: %d"), Actors.Num());
				/* i 번째 인덱스를 제거 */
				Actors.RemoveAt(i);
			}
		}
	}
	RespawnActor();
}

void AItemRespawn::RespawnActor()
{
	if (Actors.Num() < RespawnNum)
	{
		for (int i = 0; i < CurRespawnNum; i++)
		{
			if (Actors.Num() < RespawnNum)
			{
				GetRandomPointInCollisionBox();
			}
		}
	}
}

void AItemRespawn::GetRandomPointInCollisionBox()
{
	FActorSpawnParameters SpawnParams;

	FVector SpawnOrigin = CollisionMesh->Bounds.Origin;
	FVector SpawnExtent = CollisionMesh->Bounds.BoxExtent;

	const FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
	const FRotator SpawnRotation = UKismetMathLibrary::RandomRotator(true);

	ADropedItem* DropedActor;

	DropedActor = GetWorld()->SpawnActor<ADropedItem>(ADropedItem::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	DropedActor->CollisionMesh->SetBoxExtent(FVector(15.f, 15.f, 15.f));
	DropedActor->CollisionMesh->SetWorldLocation(DropedActor->MyBox->GetComponentLocation());
	DropedActor->ItemFresh(SpawnItemName);

	Actors.Add(DropedActor);
}
