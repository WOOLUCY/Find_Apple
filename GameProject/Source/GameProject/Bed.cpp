// Fill out your copyright notice in the Description page of Project Settings.


#include "Bed.h"
#include "FindAppleCharacter.h"

// Sets default values
ABed::ABed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Bed = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BED"));
	RootComponent = Bed;
	Bedding = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BEDDING"));
	Bedding->SetupAttachment(RootComponent);
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Box->SetupAttachment(RootComponent);

	Box->SetBoxExtent(FVector(125.f,100.f,100.f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BED
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/Bed.Bed'"));
	if (SM_BED.Succeeded()) {
		Bed->SetStaticMesh(SM_BED.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BEDINGE
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/bedding.bedding'"));

	if (SM_BEDINGE.Succeeded()) {
		Bedding->SetStaticMesh(SM_BEDINGE.Object);
		NotLaying = SM_BEDINGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BEDINGE_LAYING
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/bedding_charlaying.bedding_charlaying'"));
	if (SM_BEDINGE_LAYING.Succeeded()) {
		Laying = SM_BEDINGE_LAYING.Object;
	}

	Bed->SetCollisionProfileName("BlockAll");
	Bedding->SetCollisionProfileName("BlockAll");


	Box->SetCollisionProfileName("OverlapAll");

	Box->OnComponentBeginOverlap.AddDynamic(this, &ABed::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &ABed::OnOverlapEnd);


}

// Called when the game starts or when spawned
void ABed::BeginPlay()
{
	Super::BeginPlay();

	//Box->SetRelativeLocation(Bed->GetRelativeLocation());

	
}

void ABed::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	auto hero = Cast<AFindAppleCharacter>(OtherActor);
	if (hero != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("Overlap with Character"));

		if (Bedding->GetStaticMesh() == NotLaying) {
			Bedding->SetStaticMesh(Laying);
		}

		

	}
	else {
		return;
	}

}

void ABed::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void ABed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

