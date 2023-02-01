// Fill out your copyright notice in the Description page of Project Settings.


#include "Tree.h"

// Sets default values
ATree::ATree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MaxDamage = 10.f;
	TotalDamage = 0.f;
	Lower = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LOWER"));
	RootComponent = Lower;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOWER
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/LowerTree.LowerTree'"));
	if (SM_LOWER.Succeeded()) {
		Lower->SetStaticMesh(SM_LOWER.Object);
	}


	Upper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UPPER"));
	Upper->SetupAttachment(Lower);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_UPPER
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/UpperTree.UpperTree'"));
	if (SM_UPPER.Succeeded()) {
		Upper->SetStaticMesh(SM_UPPER.Object);
	}


}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATree::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvnet, AController* EvnetInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvnet, EvnetInstigator, DamageCauser);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, DamageCauser->GetName());

	
	Test(FinalDamage);


	return 0.f;
}

void ATree::Test(float Damage)
{
	if (TotalDamage > MaxDamage) {
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Wow"));
		TotalDamage = 0.f;

	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("not yet"));
		TotalDamage += Damage;
		//Upper->SetRelativeRotation(FRotator());
	}
}

