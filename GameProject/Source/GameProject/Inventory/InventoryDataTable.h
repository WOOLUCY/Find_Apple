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
	int32 ItemType;		/* ���� �� ������ 1 / eatable = 1 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FText Descript;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UStaticMesh* Mesh3D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float Hunger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FVector MeshScale;
};



UCLASS()
class GAMEPROJECT_API AInventoryDataTable : public AActor
{
	GENERATED_BODY()
};