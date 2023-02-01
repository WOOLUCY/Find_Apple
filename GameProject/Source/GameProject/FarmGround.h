// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY()
		UBoxComponent* Box;


	OnFarmDelegate PlantDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorOnClicked(FKey PressedButton) override;
	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
