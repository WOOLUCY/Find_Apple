// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipComponent.h"

// Sets default values for this component's properties
UEquipComponent::UEquipComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	Damage = 10.f;
	IsCollide = false;
}


void UEquipComponent::SetDamage(float SetDam)
{
	Damage = SetDam;
}

void UEquipComponent::CollideCheck()
{
	FHitResult HitResult;
	//히트체크를 하고 

	//토클하는거로 하자

	IsCollide = true ? false : true;

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("CollidCheck "));

}

// Called when the game starts
void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr) {
		auto hero = UGameplayStatics::GetPlayerCharacter(TheWorld, 0);
		Anim = Cast<UFindAppleAnimInstance>(hero->GetMesh()->GetAnimInstance());

		if (Anim != nullptr) {
			Anim->HitCheckStart.BindUObject(this, &UEquipComponent::CollideCheck);
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("delegate connetc "));

		}


	}
	
}


// Called every frame
void UEquipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

