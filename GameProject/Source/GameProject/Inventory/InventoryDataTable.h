// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "InventoryDataTable.generated.h"


USTRUCT(BlueprintType)
struct FInventoryTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 ItemType = 0;		/* 먹을 수 있으면 1 / eatable = 1 / not visible = 2 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FText Descript;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UTexture2D* Thumbnail = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UStaticMesh* Mesh3D = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float HP = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float Hunger = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FVector MeshScale = FVector(1.f, 1.f, 1.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int BeginningHaveCount = 0;

};



UCLASS()
class GAMEPROJECT_API AInventoryDataTable : public AActor
{
	GENERATED_BODY()
};