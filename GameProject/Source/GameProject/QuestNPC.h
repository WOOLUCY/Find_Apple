// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "QuestNPC.generated.h"

UCLASS()
class GAMEPROJECT_API AQuestNPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQuestNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USkeletalMeshComponent* SKMeshComponent;
};
