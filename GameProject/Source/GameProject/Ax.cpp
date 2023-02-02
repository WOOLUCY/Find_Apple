#include "Ax.h"
#include "Kismet/GameplayStatics.h"
#include "FindAppleCharacter.h"

AAx::AAx()
{
	PrimaryActorTick.bCanEverTick = false;

	Ax = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->InitBoxExtent(FVector(6.330199, 15.648295, 10.536008));

	RootComponent = Ax;
	CollisionBox->SetupAttachment(RootComponent);
	//위치는 블푸로 정해봐야함
	CollisionBox->SetRelativeLocation(FVector(0.f, 43.069808f, -1.848582f));
	Damage = 10.f;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_MESH
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/Ax.Ax'"));
	if (SM_MESH.Succeeded()) {
		Ax->SetStaticMesh(SM_MESH.Object);
	}

	Ax->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));


}

void AAx::BeginPlay()
{
	Super::BeginPlay();

	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr) {
		auto hero = UGameplayStatics::GetPlayerCharacter(TheWorld, 0);
		Anim = Cast<UFindAppleAnimInstance>(hero->GetMesh()->GetAnimInstance());

		if (Anim != nullptr) {
			Anim->HitCheckStart.BindUObject(this, &AAx::SetCollisionStart);
			Anim->HitCheckEnd.BindUObject(this, &AAx::SetCollisionEnd);

			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("AAx - delegate connetec "));

		}
	}
	

}

void AAx::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAx::NotifyActorBeginOverlap(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("AAx -NotifyAcotrBeginOverlap "));
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

void AAx::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	
}

void AAx::SetCollisionStart()
{
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAll"));
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("OverlapAll"));

}

void AAx::SetCollisionEnd()
{
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("NoCollision"));

}
