// Fill out your copyright notice in the Description page of Project Settings.


#include "FishingVol.h"

#include "FindAppleCharacter.h"

// Sets default values
AFishingVol::AFishingVol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FishginVolumeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FishingVolume"));
	RootComponent = FishginVolumeBox;

	FishginVolumeBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));


}

// Called when the game starts or when spawned
void AFishingVol::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFishingVol::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AFishingVol::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//Super::NotifyActorBeginOverlap(OtherActor);

	auto hero = Cast<AFindAppleCharacter>(OtherActor);

	if (hero != nullptr) {
		UE_LOG(LogClass, Warning, TEXT("Fishing Volume is overlapped"));
	}
	else {
		return;
	}
}

void AFishingVol::NotifyActorEndOverlap(AActor* OtherActor)
{
	//Super::NotifyActorEndOverlap(OtherActor);
}

// Called every frame
void AFishingVol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

