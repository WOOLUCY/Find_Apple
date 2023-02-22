// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHouse.h"

// Sets default values
APlayerHouse::APlayerHouse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	//DefaultRoot->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(0.f, -90.f, 0.f));
	SetRootComponent(DefaultRoot);

	PlayerHouseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightHouse"));
	PlayerHouseMesh->SetupAttachment(DefaultRoot);

	/* Box Static Mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/NPC_HOUSE.NPC_HOUSE'"));
	if (Mesh.Succeeded())
	{
		PlayerHouseMesh->SetStaticMesh(Mesh.Object);
		PlayerHouseMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -25.587196f), FRotator(0.f, -90.f, 0.f));
		PlayerHouseMesh->SetWorldScale3D(FVector(1.6f, 1.6f, 1.6f));
	}
}

// Called when the game starts or when spawned
void APlayerHouse::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

