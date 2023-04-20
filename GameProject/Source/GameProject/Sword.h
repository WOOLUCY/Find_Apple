// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FindAppleAnimInstance.h"
#include "Components/BoxComponent.h"
#include "Sword.generated.h"

UCLASS()
class GAMEPROJECT_API ASword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASword();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetCollisionStart();
	void SetCollisionEnd();
	
	void SetSwordVisibiltiy(bool IsVisible);

	UPROPERTY(VisibleAnywhere, Category = Sword)
		UStaticMeshComponent* Sword;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Sword)
		UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = Sword)
		float Damage;



	UPROPERTY()
		UFindAppleAnimInstance* Anim;

	UFUNCTION()
		virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UFUNCTION()
		virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
			bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void SetMesh(UStaticMesh* Mesh);
};
