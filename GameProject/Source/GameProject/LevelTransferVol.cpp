// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransferVol.h"
#include "FindAppleGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelTransferVol::ALevelTransferVol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransferVol = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVol;

	TransferVol->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void ALevelTransferVol::NotifyActorBeginOverlap(AActor* OtherActor)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	//시간도 저장할까해서 넘겨줘야나,,
	auto RecentMode = UGameplayStatics::GetGameMode(GetWorld());
	

	if (Cast<AFindAppleGameMode>(RecentMode) != nullptr) {


	}

	if (Pawn != nullptr) {
		UGameplayStatics::OpenLevel(this, *TransferLevelName);
	}
}

// Called when the game starts or when spawned
void ALevelTransferVol::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelTransferVol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

