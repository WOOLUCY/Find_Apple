// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChestBox.generated.h"

UCLASS()
class GAMEPROJECT_API AChestBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChestBox();

	UPROPERTY()
		UStaticMeshComponent* ChestMesh;

	UPROPERTY(VisibleAnywhere, Category = Damage)
		float MaxDamage;

	UPROPERTY(VisibleAnywhere, Category = Damage)
		float TotalDamage;

	UPROPERTY(VisibleAnywhere, Category = Damage)
		float RespawnTime;


	void RespawnBox();
	
	UPROPERTY()
		FName ItemName;
	

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvnet, class AController* EvnetInstigator, AActor* DamageCauser) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
