// Fill out your copyright notice in the Description page of Project Settings.


#include "Tree.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "FindAppleCharacter.h"

// Sets default values
ATree::ATree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MaxDamage = 50.f;
	TotalDamage = 0.f;
	RespawnTime = 5.f;

	Lower = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LOWER"));
	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("PIVOT"));
	Upper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UPPER"));
	Leaf = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LEAF"));

	Pivot->SetRelativeLocation(FVector(0, 0, 90.f));
	Upper->SetRelativeLocation(FVector(0, 0, -90.f));
	Leaf->SetRelativeLocation(FVector(0, 0, -90.f));

	RootComponent = Lower;
	Pivot->SetupAttachment(RootComponent);

	Upper->SetupAttachment(Pivot);

	Upper->AttachToComponent(Pivot, FAttachmentTransformRules::KeepWorldTransform);
	Leaf->AttachToComponent(Pivot, FAttachmentTransformRules::KeepWorldTransform);
	Leaf->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOWER
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/LowerTree.LowerTree'"));
	if (SM_LOWER.Succeeded()) {
		Lower->SetStaticMesh(SM_LOWER.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_UPPER
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/UpperTree.UpperTree'"));
	if (SM_UPPER.Succeeded()) {
		Upper->SetStaticMesh(SM_UPPER.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LEAF
	(TEXT("/Script/Engine.StaticMesh'/Game/untitled_category/untitled_asset/TreeWithLeafs.TreeWithLeafs'"));
	if (SM_LEAF.Succeeded()) {
		Leaf->SetStaticMesh(SM_LEAF.Object);
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

void ATree::RespawnTree()
{
	TotalDamage = 0.f;
	Pivot->SetRelativeRotation(FRotator());
	Upper->SetVisibility(true);
	Leaf->SetVisibility(true);

}

float ATree::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvnet, AController* EvnetInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvnet, EvnetInstigator, DamageCauser);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, DamageCauser->GetName());

	
	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr) {
		auto hero = UGameplayStatics::GetPlayerCharacter(TheWorld, 0);

		if (Cast<AFindAppleCharacter>(hero)) {

			if (TotalDamage > MaxDamage) {
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Wow"));
				Upper->SetVisibility(false);
				Leaf->SetVisibility(false);

				FTimerHandle Timer;

				GetWorldTimerManager().SetTimer(Timer, this, &ATree::RespawnTree, RespawnTime);

			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("not yet"));
				FVector ForAdd = hero->GetMesh()->GetRightVector();
				Pivot->AddWorldRotation(FRotator(ForAdd.Y * -3, ForAdd.Z * 3, ForAdd.X * -3));
				TotalDamage += FinalDamage;
			}
		}

	}
	return 0.f;
}


