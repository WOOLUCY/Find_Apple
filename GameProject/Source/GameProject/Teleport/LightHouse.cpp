// Fill out your copyright notice in the Description page of Project Settings.


#include "LightHouse.h"
#include "Components/SceneComponent.h"

/* -------------------------------------------------------------------------- */
// ���� �������� �����ϰ� ������ ��ġ�� ���Ϳ� "�±�"�� �߰��ؾ� �Ѵ�.
// 
// �ٸ� �� ��� - Bridge
// NPC �� �� ��� - NPChouse
// ���� �� ��� - FrontDungeon
/* -------------------------------------------------------------------------- */


// Sets default values
ALightHouse::ALightHouse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);

	LightHouseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightHouse"));
	LightHouseMesh->SetupAttachment(DefaultRoot);

	/* Box Static Mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Script/Engine.StaticMesh'/Game/Semin/Asset/LightHouse/LightHouse.LightHouse'"));
	if (Mesh.Succeeded())
	{
		LightHouseMesh->SetStaticMesh(Mesh.Object);
		LightHouseMesh->SetRelativeRotation(FRotator(0.f, -0.f, 0.f));
		LightHouseMesh->SetWorldScale3D(FVector(2.f, 2.f, 2.f));
	}


}

// Called when the game starts or when spawned
void ALightHouse::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

