// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmGround.h"

// Sets default values
AFarmGround::AFarmGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = Box;
	Mesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/MouseOverlap.MouseOverlap'"));
	if (SM_MESH.Succeeded()){
		Mesh->SetStaticMesh(SM_MESH.Object);
	}
	
	//Box->BeginComponentOverlap.ADd
	Mesh->SetVisibility(true);
}

// Called when the game starts or when spawned
void AFarmGround::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFarmGround::NotifyActorOnClicked(FKey PressedButton)
{
	if (PressedButton == EKeys::LeftMouseButton) {
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("notify actor clicked"));
	}



	PlantDelegate.ExecuteIfBound();

}

void AFarmGround::NotifyActorBeginCursorOver()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("being voer"));
	//여기서 뭐 파란색으로 표시한다거나하기

	Mesh->SetVisibility(true);



}

void AFarmGround::NotifyActorEndCursorOver()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("being End"));
	//여기서 뭐 파란색으로 표시한다거나하기

	Mesh->SetVisibility(false);

}

// Called every frame
void AFarmGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

