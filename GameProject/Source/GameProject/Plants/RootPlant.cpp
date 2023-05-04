// Fill out your copyright notice in the Description page of Project Settings.


#include "RootPlant.h"
#include "Kismet/GameplayStatics.h"
#include "../Inventory/InventoryComponent.h"

#include "../FindAppleCharacter.h"

ARootPlant::ARootPlant()
{
	LiveDay = 0;
	MaxDeathDay = 1;
	DeathCount = 0;
	IsFruit = false;

	Current = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CurrentMesh"));
	RootComponent = Current;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_VEG1
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/rootplant1.rootplant1'"));

	if (SM_VEG1.Succeeded()) {
		Meshs.Add(SM_VEG1.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_VEG2
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/rootplant2.rootplant2'"));
	if (SM_VEG2.Succeeded()) {
		Meshs.Add(SM_VEG2.Object);
	}


	//��
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_ROOT1
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/rootplatn3.rootplatn3'"));
	if (SM_ROOT1.Succeeded()) {
		Roots.Add(SM_ROOT1.Object);
		//�ϴ� ���� �س�
		Meshs.Add(SM_ROOT1.Object);

	}
	//���
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_ROOT2
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/Carrot.Carrot'"));
	if (SM_ROOT2.Succeeded()) {
		Roots.Add(SM_ROOT2.Object);
	}



	Current->SetCollisionProfileName("NoCollision");

}

void ARootPlant::BeginPlay()
{
	Super::BeginPlay();

	//�����ϰ� �������ֱ� - �׷� �κ��丮 ������ ��¥??
	


}

void ARootPlant::AddInventory()
{
	UE_LOG(LogTemp, Warning, TEXT("RootPlant Int AddInvetory Function"));
	//���⼭ �κ��� �־��ָ�ȴ�.
	auto* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);
	if(MyCharacter!=nullptr){
		FName ItemName = "Radish";
		//MyCharacter->InventoryComponent
		MyCharacter->InventoryComponent->AddToInventory(ItemName, 1);

	}


}
