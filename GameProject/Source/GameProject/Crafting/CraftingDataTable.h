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
	// 제작 물품의 이름은 행이름으로 하고
	// 재료별 이름(=행 이름)과 개수
	// PNG 넣는다면 Texture
	// 돈이 있다면 돈
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	FText DisplayName;		/* 아이템 제작 창에 출력될 이름 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 apple = 0;		/* row name이 apple이다. apple이 필요한 개수 */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* AppleTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 orange = 0;		/* Orange가 필요한 개수 */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* OrangeTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 branch = 0;		/* branch(나뭇가지)가 필요한 개수 */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* BranchTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 rock = 0;			/* rock(돌멩이)가 필요한 개수 */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* RockTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 trunk = 0;			/* Trunk(통나무)가 필요한 개수 */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* TrunkTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 gold = 0;			/* Gold(금)가 필요한 개수 */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* GoldTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 iron = 0;			/* Iron(철)이 필요한 개수 */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* IronTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 rubby = 0;			/* Rubby(루비)가 필요한 개수 */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* RubbyTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 sapphire = 0;			/* Sapphire(사파이어)가 필요한 개수 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* SapphireTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);


	/************ Tool ************/
	/* Pick */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* PickTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 pick = 0;			

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* Pick1Texture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 pick1 = 0;			
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* Pick2Texture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 pick2 = 0;			
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* Pick3Texture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 pick3 = 0;			
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* Pick4Texture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 pick4 = 0;			

	/* AX */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* AXTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 AX = 0;		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* AX1Texture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 AX1 = 0;		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* AX2Texture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 AX2 = 0;		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* AX3Texture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 AX3 = 0;		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* AX4Texture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 AX4 = 0;		


	/* Sword */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* SwordTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 sword = 0;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* Sword1Texture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 sword1 = 0;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* Sword2Texture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 sword2 = 0;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* Sword3Texture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 sword3 = 0;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* Sword4Texture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int32 sword4 = 0;	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UTexture2D* CraftTexture = UTexture2D::CreateTransient(128, 128, PF_R8G8B8A8);
};


UCLASS()
class GAMEPROJECT_API ACraftingDataTable : public AActor
{
	GENERATED_BODY()
	
};