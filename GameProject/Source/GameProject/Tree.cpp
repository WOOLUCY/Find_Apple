// Fill out your copyright notice in the Description page of Project Settings.

#include "Tree.h"
#include "Inventory/DropedItem.h"
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
	Leaf->SetupAttachment(Pivot);

	Upper->GetAttachParent();
	Leaf->GetAttachParent();
	Leaf->SetCollisionProfileName(TEXT("NoCollision"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOWER
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeLower0.TreeLower0'"));
	if (SM_LOWER.Succeeded()) {
		Lower->SetStaticMesh(SM_LOWER.Object);
	}
	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_UPPER
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeUpper0.TreeUpper0'"));
	if (SM_UPPER.Succeeded()) {
		Upper->SetStaticMesh(SM_UPPER.Object);

	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LEAF
	(TEXT("/Script/Engine.StaticMesh'/Game/untitled_category/untitled_asset/TreeWithLeafs.TreeWithLeafs'"));
	if (SM_LEAF.Succeeded()) {
		Leaf->SetStaticMesh(SM_LEAF.Object);
	}

	


	int RandonNumber = FMath::RandRange(0, 3);

	switch (RandonNumber)
	{
	case 0:


		break;
	case 1:
		SM_LOWER = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeLower1.TreeLower1'"));
		if (SM_LOWER.Succeeded()) {
			Lower->SetStaticMesh(SM_LOWER.Object);
		}
		SM_UPPER = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeUpper1.TreeUpper1'"));
		if (SM_UPPER.Succeeded()) {
			Upper->SetStaticMesh(SM_UPPER.Object);
		}

		break;
	case 2:
		SM_LOWER = ConstructorHelpers::FObjectFinder<UStaticMesh> (TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeLower2.TreeLower2'"));
		if (SM_LOWER.Succeeded()) {
			Lower->SetStaticMesh(SM_LOWER.Object);
		}
		SM_UPPER = ConstructorHelpers::FObjectFinder<UStaticMesh> (TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeUpper2.TreeUpper2'"));
		if (SM_UPPER.Succeeded()) {
			Upper->SetStaticMesh(SM_UPPER.Object);
		}

		break;
	case 3:
		SM_LOWER = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeLower3.TreeLower3'"));
		if (SM_LOWER.Succeeded()) {
			Lower->SetStaticMesh(SM_LOWER.Object);
		}
		SM_UPPER = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeUpper3.TreeUpper3'"));
		if (SM_UPPER.Succeeded()) {
			Upper->SetStaticMesh(SM_UPPER.Object);
		}

		break;

	default:
		break;
	}


	RandonNumber = FMath::RandRange(0, 100);

	switch (RandonNumber)
	{
	case 0:

		break;
	case 1:
		SM_LEAF =  ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("/Script/Engine.StaticMesh'/Game/untitled_category/untitled_asset/TreeWithLeafs01.TreeWithLeafs01'"));
		if (SM_LEAF.Succeeded()) {
			Leaf->SetStaticMesh(SM_LEAF.Object);

		}

		break;
	case 2:
		SM_LEAF = ConstructorHelpers::FObjectFinder<UStaticMesh>
			(TEXT("/Script/Engine.StaticMesh'/Game/untitled_category/untitled_asset/TreeWithLeafs02.TreeWithLeafs02'"));
		if (SM_LEAF.Succeeded()) {
			Leaf->SetStaticMesh(SM_LEAF.Object);

		}

		break;

	default:
		break;
	}

}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();


}

void ATree::PostInitializeComponents()
{
	Super::PostInitializeComponents();
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

	static bool once = true;

	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr) {
		auto hero = UGameplayStatics::GetPlayerCharacter(TheWorld, 0);

		if (Cast<AFindAppleCharacter>(hero)) {

			if (TotalDamage > MaxDamage) {
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Wow"));
				Upper->SetVisibility(false);
				Leaf->SetVisibility(false);
				
				FVector PivotWorld = GetTransform().TransformPosition(Pivot->GetRelativeLocation());
				if (once) {
					ADropedItem* DropedActor = GetWorld()->SpawnActor<ADropedItem>(PivotWorld, FRotator::ZeroRotator);
					DropedActor->ItemFresh("trunk");
					once = false;
				}

				FTimerHandle Timer;
				GetWorldTimerManager().SetTimer(Timer, this, &ATree::RespawnTree, RespawnTime);

			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("not yet"));
				FVector ForAdd = hero->GetMesh()->GetRightVector();
				Pivot->AddWorldRotation(FRotator(ForAdd.Y * -3, ForAdd.Z * 3, ForAdd.X * -3));
				TotalDamage += FinalDamage;
				once = true;
			}
		}

	}
	return 0.f;
}


