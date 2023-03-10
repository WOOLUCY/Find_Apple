// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransferVol.h"
#include "FindAppleGameMode.h"
#include "MyGameInstance.h"
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
	auto RecentMode = UGameplayStatics::GetGameMode(GetWorld());
	
	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr) {
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		AFindAppleGameMode* MyMode = Cast<AFindAppleGameMode>(GameMode);

		auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (GameInstance != nullptr) {
			FString LevelName = UGameplayStatics::GetCurrentLevelName(TheWorld);
			FString Name = "MainMap1";
			if (LevelName.Equals(Name)) {

				UE_LOG(LogTemp, Warning, TEXT("LevelTransfer cpp eqaul"));
				FVector temp = TransferVol->GetRelativeLocation();
				FVector ForwardVector = TransferVol->GetForwardVector();
				FVector MoveDirection = ForwardVector * 200;
				FVector NewLocation = temp + MoveDirection;
				GameInstance->SetCharLoc(NewLocation);

			}

		}
	}
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

void ALevelTransferVol::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ALevelTransferVol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

