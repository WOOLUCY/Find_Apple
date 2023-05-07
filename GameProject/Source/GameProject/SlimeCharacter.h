// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlimeCharacter.generated.h"

UCLASS()
class GAMEPROJECT_API ASlimeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlimeCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool IsAttacked = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool IsAttacking = false;

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

	UPROPERTY()
	bool IsDead = false;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};