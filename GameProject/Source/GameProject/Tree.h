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

	void Test(float Damage);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadWrite, Category = Tree)
		UStaticMeshComponent* Lower;

	UPROPERTY(BlueprintReadWrite, Category = Tree)
		UStaticMeshComponent* Upper;

	UPROPERTY(BlueprintReadWrite, Category=Damage)
		float MaxDamage;
	UPROPERTY(BlueprintReadWrite, Category = Damage)
		float TotalDamage;



};
