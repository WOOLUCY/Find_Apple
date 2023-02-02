// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmGround.h"

// Sets default values
AFarmGround::AFarmGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	CheckMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckMesh"));

	Overlap = CreateDefaultSubobject<UMaterial>(TEXT("BLUE"));
	NotWet = CreateDefaultSubobject<UMaterial>(TEXT("NotWet"));
	Wet = CreateDefaultSubobject<UMaterial>(TEXT("Wet"));


	RootComponent = Box;
	Box->SetRelativeScale3D(FVector(1.5f, 1.5, 0.5f));
	Mesh->SetupAttachment(RootComponent);
	CheckMesh->SetupAttachment(Mesh);

	Mesh->SetCollisionProfileName("NoCollision");
	Box->SetCollisionProfileName("OverlapAll");

	IsEmpty = false;
	CanPutSeed = false;
	IsWet = false;


	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/MouseOverlap.MouseOverlap'"));
	if (SM_MESH.Succeeded()){
		Mesh->SetStaticMesh(SM_MESH.Object);
		CheckMesh->SetStaticMesh(SM_MESH.Object);
		CheckMesh->SetRelativeLocation(FVector(0, 0, 1));
	}

	
	//머터리얼불러오기
	static ConstructorHelpers::FObjectFinder<UMaterial>Mat_Blue
	(TEXT("/Script/Engine.Material'/Game/kaon/asset/material/M_GroundBlue.M_GroundBlue'"));
	if (Mat_Blue.Succeeded()) {
		CheckMesh->SetMaterial(0, Mat_Blue.Object);
		CheckMesh->SetVisibility(false);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>Mat_Wet
	(TEXT("/Script/Engine.Material'/Game/kaon/asset/material/M_Wet.M_Wet'"));
	if (Mat_Wet.Succeeded()) {
		Wet = Mat_Wet.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>Mat_NotWet
	(TEXT("/Script/Engine.Material'/Game/kaon/asset/material/M_NotWet.M_NotWet'"));
	if (Mat_NotWet.Succeeded()) {
		NotWet = Mat_NotWet.Object;
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
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("being dfkldkfldf"));
	//여기서 뭐 파란색으로 표시한다거나하기

	CheckMesh->SetVisibility(true);



}

void AFarmGround::NotifyActorEndCursorOver()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("being End"));
	//여기서 뭐 파란색으로 표시한다거나하기

	CheckMesh->SetVisibility(false);

}

// Called every frame
void AFarmGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

