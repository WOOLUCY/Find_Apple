// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "DialogueDataStruct.generated.h"


USTRUCT(BlueprintType)
struct FDialogueTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 NPC_ID = 500;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText NPC_Name;				// NPC 의 이름	
			
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 Conversation_ID = 0;	// 다이얼로그의 진행 상태 같은 것. 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 Line_ID = 0;			// 현재 말하고 있는 NPC 의 대사 줄
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText Dialogue;				// 대사 내용 (스크립트)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText Answer1;				// 나의 대답 1
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText Answer2;				// 나의 대답 2
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FName Conditions_Item;		// 퀘스트 필요 아이템
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 Conditions_cnt = 0;	// 퀘스트 필요 아이템의 개수	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FName Reward;				// 보상
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 Reward_cnt = 0;		// 보상 개수
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 Next_Conversation_ID = 0;	// 다음 다이얼로그 진행을 위한 수 (걍 ++ 하면 다음 내용으로)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText QuestTitle;			// UI에 나오게 될 퀘스트의 이름
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText QuestDes;				// UI에 나오게 될 간략한 퀘스트 내용

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FName PlaceName;				// UI에 나오게 될 간략한 퀘스트 내용
};


UCLASS()
class GAMEPROJECT_API ADialogueDataTable : public AActor
{
	GENERATED_BODY()
};