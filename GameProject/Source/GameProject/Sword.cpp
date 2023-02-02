// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "Kismet/GameplayStatics.h"
#include "FindAppleCharacter.h"

// Sets default values
ASword::ASword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SWORD"));
	RootComponent = Sword;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(0.06f, 0.73f, 0.04f));
	CollisionBox->SetRelativeLocation(FVector(0.f, 37.191134f, 0.f));


	Damage = 10.f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SWORD
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/Sword.Sword'"));
	if (SM_SWORD.Succeeded()) {
		Sword->SetStaticMesh(SM_SWORD.Object);
	}
	Sword->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));


}

// Called when the game starts or when spawned
void ASword::BeginPlay()
{
	Super::BeginPlay();

	//흠냐 포스트로 옮길까??
	//득우띠는 포스트, 도란이는 비긴플레이 어디가 좋을지 흠냐흠냐
	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr) {
		auto hero = UGameplayStatics::GetPlayerCharacter(TheWorld, 0);
		Anim = Cast<UFindAppleAnimInstance>(hero->GetMesh()->GetAnimInstance());

		if (Anim != nullptr) {
			Anim->HitCheckStart.BindUObject(this, &ASword::SetCollisionStart);
			Anim->HitCheckEnd.BindUObject(this, &ASword::SetCollisionEnd);

			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("delegate connetec "));

		}
	}

}

// Called every frame
void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASword::SetCollisionStart()
{
	//근데 스월드는 항상 노콜리전임 박스를바꿔줘야함
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAll"));
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("SetCollisionStart "));


}

void ASword::SetCollisionEnd()
{
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("SetCollisionEnd "));

}

void ASword::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("NotifyActorBeginOverlap "));

	//걍 쓴거임 지워도됨
	FString name = OtherActor->GetName();
	
	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr) {
		auto hero = UGameplayStatics::GetPlayerCharacter(TheWorld, 0);
		if (Cast<AFindAppleCharacter>(OtherActor) != hero) {
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, name);
			//데미지를주겠다.

			FDamageEvent DamageEvent;
			OtherActor->TakeDamage(Damage, DamageEvent, UGameplayStatics::GetPlayerController(TheWorld, 0), this);
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("TakeDamage"));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("OverlapSelf"));
		}
	}


}

void ASword::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("NotifyHit "));

	//피해를 주겠다.
	FDamageEvent DamageEvent;
	//Hit.GetActor()->TakeDamage()

}

