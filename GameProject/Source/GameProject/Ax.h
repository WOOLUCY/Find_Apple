// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FindAppleAnimInstance.h"
#include "Components/BoxComponent.h"
#include "Ax.generated.h"

UCLASS()
class GAMEPROJECT_API AAx : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAx();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, Category = Ax)
		UStaticMeshComponent* Ax;

	UPROPERTY(VisibleAnywhere, Category = Ax)
		UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = Ax)
		float Damage;

	UPROPERTY()
		UFindAppleAnimInstance* Anim;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UFUNCTION()
		virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
			bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void SetCollisionStart();
	void SetCollisionEnd();


};
