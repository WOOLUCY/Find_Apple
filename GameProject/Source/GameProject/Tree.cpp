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
	RespawnTime = 20.f;
	

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

	//lower
	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOWER
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeLower0.TreeLower0'"));
	if (SM_LOWER.Succeeded()) {
		Lowers[0]= SM_LOWER.Object;

	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOWER1
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeLower1.TreeLower1'"));
	if (SM_LOWER1.Succeeded()) {
		Lowers[1] = SM_LOWER1.Object;
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LOWER2
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeLower2.TreeLower2'"));
	if (SM_LOWER2.Succeeded()) {
		Lowers[2]=SM_LOWER2.Object;
	}



	//upper
	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_UPPER
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeUpper0.TreeUpper0'"));
	if (SM_UPPER.Succeeded()) {
		Uppers[0] = SM_UPPER.Object;

	}
	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_UPPER1
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeUpper1.TreeUpper1'"));
	if (SM_UPPER1.Succeeded()) {
		Uppers[1] = SM_UPPER1.Object;

	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_UPPER2
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/TreeUpper2.TreeUpper2'"));
	if (SM_UPPER2.Succeeded()) {
		Uppers[2] = SM_UPPER2.Object;

	}




	//leaf
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LEAF
	(TEXT("/Script/Engine.StaticMesh'/Game/untitled_category/untitled_asset/TreeWithLeafs.TreeWithLeafs'"));
	if (SM_LEAF.Succeeded()) {
		Leaf->SetStaticMesh(SM_LEAF.Object);
		Leafs[0] = SM_LEAF.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LEAF1
	(TEXT("/Script/Engine.StaticMesh'/Game/untitled_category/untitled_asset/TreeWithLeafs01.TreeWithLeafs01'"));
	if (SM_LEAF1.Succeeded()) {
		Leafs[1] = SM_LEAF1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LEAF2
	(TEXT("/Script/Engine.StaticMesh'/Game/untitled_category/untitled_asset/TreeWithLeafs02.TreeWithLeafs02'"));
	if (SM_LEAF2.Succeeded()) {
		Leafs[2] = SM_LEAF2.Object;
	}






	//semin Material
	static FString Material01Name = "/Script/Engine.MaterialInstanceConstant'/Game/Semin/Material/M_Occlusion_TreeStump.M_Occlusion_TreeStump'";
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material01Asset(*Material01Name);
	StumpMaterial = Material01Asset.Object;

	static FString Material02Name = "/Script/Engine.MaterialInstanceConstant'/Game/Semin/Material/M_Occlusion_TreeHead1.M_Occlusion_TreeHead1'";
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material02Asset(*Material02Name);
	FirstTreeMaterial1 = Material02Asset.Object;

	static FString Material03Name = "/Script/Engine.MaterialInstanceConstant'/Game/Semin/Material/M_Occlusion_TreeHead2.M_Occlusion_TreeHead2'";
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material03Asset(*Material03Name);
	FirstTreeMaterial2 = Material03Asset.Object;

	static FString Material04Name = "/Script/Engine.MaterialInstanceConstant'/Game/Semin/Material/M_Occlusion_TreeHead3.M_Occlusion_TreeHead3'";
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material04Asset(*Material04Name);
	FirstTreeMaterial3 = Material04Asset.Object;

	static FString Material05Name = "/Script/Engine.MaterialInstanceConstant'/Game/Semin/Material/M_Occlusion_TreeLongHead1.M_Occlusion_TreeLongHead1'";
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material05Asset(*Material05Name);
	SecondTreeMaterial1 = Material05Asset.Object;

	static FString Material06Name = "/Script/Engine.MaterialInstanceConstant'/Game/Semin/Material/M_Occlusion_TreeLongHead2.M_Occlusion_TreeLongHead2'";
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material06Asset(*Material06Name);
	SecondTreeMaterial2 = Material06Asset.Object;

	static FString Material07Name = "/Script/Engine.MaterialInstanceConstant'/Game/Semin/Material/M_Occlusion_TreeLongHead3.M_Occlusion_TreeLongHead3'";
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material07Asset(*Material07Name);
	SecondTreeMaterial3 = Material07Asset.Object;

	static FString Material08Name = "/Script/Engine.MaterialInstanceConstant'/Game/Semin/Material/M_Occlusion_TreePinkHead.M_Occlusion_TreePinkHead'";
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material08Asset(*Material08Name);
	ThirdTreeMaterial1 = Material08Asset.Object;
}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();
	float RandYaw = FMath::RandRange(-90.f, 90.f);

	SetActorRelativeRotation(FRotator(0.f, RandYaw,0.f));

	int RandonNumber = FMath::RandRange(0, 2);

	Lower->SetMaterial(0, StumpMaterial);
	Upper->SetMaterial(0, StumpMaterial);
	//semin
	Lower->SetCollisionProfileName(TEXT("Tree"));
	Upper->SetCollisionProfileName(TEXT("Tree"));

	if (RandonNumber == 0) 
	{
		Leaf->SetMaterial(0, StumpMaterial);
		Leaf->SetMaterial(1, FirstTreeMaterial1);
		Leaf->SetMaterial(2, FirstTreeMaterial2);
		Leaf->SetMaterial(3, FirstTreeMaterial3);
	}

	else if (RandonNumber == 1) 
	{
		Leaf->SetMaterial(0, SecondTreeMaterial1);
		Leaf->SetMaterial(1, SecondTreeMaterial2);
		Leaf->SetMaterial(2, SecondTreeMaterial3);
	}

	else 
	{
		Leaf->SetMaterial(0, ThirdTreeMaterial1);
	}

	Leaf->SetStaticMesh(Leafs[RandonNumber]);

	RandonNumber = FMath::RandRange(0, 2);
	Upper->SetStaticMesh(Uppers[RandonNumber]);

	RandonNumber = FMath::RandRange(0, 2);
	Lower->SetStaticMesh(Lowers[RandonNumber]);




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
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, DamageCauser->GetName());

	static bool once = true;

	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr) {
		auto hero = UGameplayStatics::GetPlayerCharacter(TheWorld, 0);

		if (Cast<AFindAppleCharacter>(hero)) {

			if (TotalDamage > MaxDamage) {
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Wow"));
				Upper->SetVisibility(false);
				Leaf->SetVisibility(false);
				
				FVector PivotWorld = GetTransform().TransformPosition(Pivot->GetRelativeLocation());
				if (once) {
					ADropedItem* DropedActor = GetWorld()->SpawnActor<ADropedItem>(PivotWorld+FVector(0,0,20.f), FRotator::ZeroRotator);
					DropedActor->ItemFresh("trunk");
					once = false;
				}

				FTimerHandle Timer;
				GetWorldTimerManager().SetTimer(Timer, this, &ATree::RespawnTree, RespawnTime);

			}
			else {
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("not yet"));
				FVector ForAdd = hero->GetMesh()->GetRightVector();
				Pivot->AddWorldRotation(FRotator(ForAdd.Y * -3, ForAdd.Z * 3, ForAdd.X * -3));
				TotalDamage += FinalDamage;
				once = true;
			}
		}

	}
	return 0.f;
}


