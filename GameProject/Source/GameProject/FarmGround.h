// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FindAppleAnimInstance.h"
#include "Components/BoxComponent.h"
#include "FarmGround.generated.h"

DECLARE_DELEGATE(OnFarmDelegate)
UCLASS()
class GAMEPROJECT_API AFarmGround : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFarmGround();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* CheckMesh;


	UPROPERTY(VisibleAnywhere)
		UBoxComponent* Box;

	UPROPERTY()
		UMaterial* Wet;
	UPROPERTY()
		UMaterial* NotWet;
	UPROPERTY()
		UMaterial* Overlap;



	OnFarmDelegate PlantDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorOnClicked(FKey PressedButton) override;
	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;
	virtual void PostInitializeComponents() override;

private:
	bool IsEmpty;
	bool CanPutSeed;
	bool IsWet;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY()
		UFindAppleAnimInstance* Anim;

	void ReleaseSeed();
	void GrabSeed();


};