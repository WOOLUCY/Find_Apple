// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestNPC.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AQuestNPC::AQuestNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_NPC(TEXT("SkeletalMesh'/Game/Semin/Character/SKM_NPC.SKM_NPC'"));
	if (SK_NPC.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_NPC.Object);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.f), FRotator(0.0f, 270.0f, 0.0f));
	//GetMesh()->SetAnimClass()
}

// Called when the game starts or when spawned
void AQuestNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuestNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AQuestNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

