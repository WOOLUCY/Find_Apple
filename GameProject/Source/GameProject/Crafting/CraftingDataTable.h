// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "CraftingDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCraftingTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// ���� ��ǰ�� �̸��� ���̸����� �ϰ�
	// ��Ằ �̸�(=�� �̸�)�� ����
	// PNG �ִ´ٸ� Texture
	// ���� �ִٸ� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 apple = 0;		/* row name�� apple�̴�. apple�� �ʿ��� ���� */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* AppleTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 orange = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* OrangeTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* CraftTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);
};


UCLASS()
class GAMEPROJECT_API ACraftingDataTable : public AActor
{
	GENERATED_BODY()
	
};