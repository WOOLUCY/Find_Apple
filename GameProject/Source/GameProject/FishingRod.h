// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FindAppleAnimInstance.h"
#include "FishingRod.generated.h"

UCLASS()
class GAMEPROJECT_API AFishingRod : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFishingRod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Rod)
		UStaticMeshComponent* Rod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* ItemDataTable;

	TArray<struct FInventoryTableRow*> InventoryData;

	bool isOwn = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetRodVisibility(bool _in);
};
