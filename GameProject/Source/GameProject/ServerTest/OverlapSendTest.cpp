// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlapSendTest.h"
#include "Kismet/GameplayStatics.h"

//#include "../MyGameInstance.h"

// Sets default values
AOverlapSendTest::AOverlapSendTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TransferVol = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVol;

	MyInstance = nullptr;

}

// Called when the game starts or when spawned
void AOverlapSendTest::BeginPlay()
{
	Super::BeginPlay();
	MyInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

}

// Called every frame
void AOverlapSendTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MyInstance->MySocket.PacketRecv();
}

void AOverlapSendTest::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	//UE_LOG(LogTemp, Warning, TEXT("NotifyActorBeginOverlap"));
	int ItemCount = rand();
	int ItemPrice = rand();
	UE_LOG(LogTemp, Warning, TEXT("AOverlapSendTest, [%d, %d]"), ItemCount, ItemPrice);

	MyInstance->MySocket.SendTestSalePacket(ItemCount, ItemPrice);

	//MyInstance->MySocket.SendTestPacket();
}

void AOverlapSendTest::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

}

