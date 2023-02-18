// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tree.generated.h"

UCLASS()
class GAMEPROJECT_API ATree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATree();
	
	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvnet, class AController* EvnetInstigator, AActor* DamageCauser) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, Category = Tree)
		UStaticMeshComponent* Lower;

	UPROPERTY(VisibleAnywhere, Category = Tree)
		UStaticMeshComponent* Upper;

	UPROPERTY(VisibleAnywhere,  Category = Tree)
		UStaticMeshComponent* Leaf;

	UPROPERTY(VisibleAnywhere,  Category = Tree)
		USceneComponent* Pivot;

	UPROPERTY(VisibleAnywhere, Category=Damage)
		float MaxDamage;

	UPROPERTY(VisibleAnywhere, Category = Damage)
		float TotalDamage;

	void RespawnTree();

private:
	
	float RespawnTime;

	

};
