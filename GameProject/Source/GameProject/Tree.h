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

	UStaticMesh* Leafs[3];
	UStaticMesh* Uppers[3];
	UStaticMesh* Lowers[3];

	UPROPERTY(VisibleAnywhere, Category=Damage)
		float MaxDamage;

	UPROPERTY(VisibleAnywhere, Category = Damage)
		float TotalDamage;

	void RespawnTree();

	// Semin Material
	UPROPERTY(EditAnywhere, Category = "Interaction")
	UMaterialInterface* StumpMaterial = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	UMaterialInterface* FirstTreeMaterial1 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	UMaterialInterface* FirstTreeMaterial2 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	UMaterialInterface* FirstTreeMaterial3 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	UMaterialInterface* SecondTreeMaterial1 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	UMaterialInterface* SecondTreeMaterial2 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	UMaterialInterface* SecondTreeMaterial3 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	UMaterialInterface* ThirdTreeMaterial1 = nullptr;


private:
	
	float RespawnTime;

	

};
