// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DoOnce.h"
#include "ChestCharacter.generated.h"

UCLASS()
class GAMEPROJECT_API AChestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChestCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
		float Health = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
		bool IsAttacked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
		bool IsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
		bool IsOpen = false;

	FDoOnce DoOnce;

	int AttackNum = 0;
	
	UPROPERTY()
	bool IsDead = false;

	UPROPERTY(EditAnywhere, Category = "Interaction")
		UMaterialInterface* Material01 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interaction")
		UMaterialInterface* Material02 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interaction")
		UMaterialInterface* Material03 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interaction")
		UMaterialInterface* Material04 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interaction")
		UMaterialInterface* Material05 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interaction")
		UMaterialInterface* DissolveMaterial = nullptr;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	

};
