// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "DialogueDataStruct.generated.h"


USTRUCT(BlueprintType)
struct FDialogueTableStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 NPC_ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 Conversation_ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 Line_ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText Dialogue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText NPC_Name;
};


UCLASS()
class GAMEPROJECT_API ADialogueDataStruct : public AActor
{
	GENERATED_BODY()
};