// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FindAppleAnimInstance.h"
#include "Components/BoxComponent.h"

#include "Pick.generated.h"

UCLASS()
class GAMEPROJECT_API APick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APick();

	void SetCollisionStart();
	void SetCollisionEnd();


	void SetPickVisibiltiy(bool IsVisible);

	UPROPERTY(VisibleAnywhere, Category = Pick)
		UStaticMeshComponent* Pick;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Pick)
		UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = Pick)
		float Damage;

	UPROPERTY()
		UFindAppleAnimInstance* Anim;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UFUNCTION()
		virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
			bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void SetMesh(UStaticMesh* Mesh);

};
