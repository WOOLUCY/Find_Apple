// Fill out your copyright notice in the Description page of Project Settings.


#include "Pick.h"

// Sets default values
APick::APick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Pick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->InitBoxExtent(FVector(6.330199, 15.648295, 10.536008));

	RootComponent = Pick;
	CollisionBox->SetupAttachment(RootComponent);
	//위치는 블푸로 정해봐야함
	CollisionBox->SetRelativeLocation(FVector(0.f, 43.069808f, -1.848582f));
	Damage = 10.f;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_MESH
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/Pick.Pick'"));
	if (SM_MESH.Succeeded()) {
		Pick->SetStaticMesh(SM_MESH.Object);
	}

	Pick->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));


}

void APick::SetCollisionStart()
{
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAll"));
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("OverlapAll"));

}

void APick::SetCollisionEnd()
{
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("NoCollision"));

}

void APick::SetPickVisibiltiy(bool IsVisible)
{
	Pick->SetVisibility(IsVisible);

}

// Called when the game starts or when spawned
void APick::BeginPlay()
{
	Super::BeginPlay();

	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr) {
		auto hero = UGameplayStatics::GetPlayerCharacter(TheWorld, 0);
		Anim = Cast<UFindAppleAnimInstance>(hero->GetMesh()->GetAnimInstance());

		if (Anim != nullptr) {
			Anim->HitCheckStart.BindUObject(this, &APick::SetCollisionStart);
			Anim->HitCheckEnd.BindUObject(this, &APick::SetCollisionEnd);

			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Pick - delegate connetec "));

		}
	}


}

// Called every frame
void APick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APick::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//일단 야긴 빼고 
}

void APick::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
}

