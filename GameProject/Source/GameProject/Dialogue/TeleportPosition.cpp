// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportPosition.h"

// Sets default values
ATeleportPosition::ATeleportPosition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightHouse"));
	Mesh->SetupAttachment(DefaultRoot);
	
	/* Static Mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObject(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	if (MeshObject.Succeeded())
	{
		Mesh->SetStaticMesh(MeshObject.Object);
		//Mesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		Mesh->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
		Mesh->SetHiddenInGame(true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		Mesh->SetCollisionProfileName(TEXT("ItemCollision"));
	}

	// Timeline
	ConstructorHelpers::FObjectFinder<UCurveFloat>  CurveObject(TEXT("/Script/Engine.CurveFloat'/Game/Semin/UI/Map/CameraMove.CameraMove'"));
	if (CurveObject.Succeeded())
	{
		CurveFloat = CurveObject.Object;
	}
}

void ATeleportPosition::OnActivate_Implementation()
{
}

// Called when the game starts or when spawned
void ATeleportPosition::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportPosition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleportPosition::TimelineProgress(float Value)
{
}

void ATeleportPosition::TimelineFinished()
{
}

