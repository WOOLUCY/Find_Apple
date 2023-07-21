// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleTree.h"

AAppleTree::AAppleTree()
{
	LiveDay = 0;
	MaxDeathDay = 1;
	DeathCount = 0;
	IsFruit = true;
	MaxLevel = 4;

	ItemName = "Apple";
	Current = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CurrentMesh"));

	RootComponent = Current;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_TREE1
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/vegetation02.vegetation02'"));
	if (SM_TREE1.Succeeded()) {
		Meshs.Add(SM_TREE1.Object);
		
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_TREE2
	(TEXT("/Script/Engine.StaticMesh'/Game/Woo/Tree/Trunks/Trunk02.Trunk02'"));
	if (SM_TREE2.Succeeded()) {
		Meshs.Add(SM_TREE2.Object);

	}

	//여기부터 다시넣어야함
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_TREE3
	(TEXT("/Script/Engine.StaticMesh'/Game/Woo/Tree/Real/Tree0.Tree0'"));
	if (SM_TREE3.Succeeded()) {
		Meshs.Add(SM_TREE3.Object);

	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_TREE4
	(TEXT("/Script/Engine.StaticMesh'/Game/Woo/Tree/Real/AppleTree1.AppleTree1'"));
	if (SM_TREE4.Succeeded()) {
		Meshs.Add(SM_TREE4.Object);

	}



	Current->SetCollisionProfileName("NoCollision");

}

void AAppleTree::BeginPlay()
{
	Super::BeginPlay();

}

void AAppleTree::PutWater()
{
	Super::PutWater();
}
