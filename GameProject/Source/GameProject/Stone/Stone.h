// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "Stone.generated.h"

UCLASS()
class GAMEPROJECT_API AStone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStone();
	

	UPROPERTY(VisibleAnywhere, Category = Damage)
		float MaxDamage;
	UPROPERTY(VisibleAnywhere, Category = Damage)
		float TotalDamage;

	
	UPROPERTY()
		UStaticMeshComponent* mesh;

	UPROPERTY()
		UPointLightComponent* light;
		
	void RespawnStone();
	FName name;

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvnet, class AController* EvnetInstigator, AActor* DamageCauser) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float RespawnTime;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
