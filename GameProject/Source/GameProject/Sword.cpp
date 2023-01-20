// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"

// Sets default values
ASword::ASword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SWORD"));
	RootComponent = Sword;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SWORD
		(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/Sword.Sword'"));
	if (SM_SWORD.Succeeded()) {
		Sword->SetStaticMesh(SM_SWORD.Object);
	}

	//충돌설정해야함일단 노콜리전
	Sword->SetCollisionProfileName(TEXT("NoCollision"));


}

// Called when the game starts or when spawned
void ASword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

