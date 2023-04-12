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
	FText NPC_Name;				// NPC �� �̸�	
			
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 Conversation_ID = 0;	// ���̾�α��� ���� ���� ���� ��. 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 Line_ID = 0;			// ���� ���ϰ� �ִ� NPC �� ��� ��
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText Dialogue;				// ��� ���� (��ũ��Ʈ)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText Answer1;				// ���� ��� 1
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText Answer2;				// ���� ��� 2
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FName Conditions_Item;		// ����Ʈ �ʿ� ������
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 Conditions_cnt = 0;	// ����Ʈ �ʿ� �������� ����	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FName Reward;				// ����
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 Reward_cnt = 0;		// ���� ����
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 Next_Conversation_ID = 0;	// ���� ���̾�α� ������ ���� �� (�� ++ �ϸ� ���� ��������)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText QuestTitle;			// UI�� ������ �� ����Ʈ�� �̸�
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText QuestDes;				// UI�� ������ �� ������ ����Ʈ ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FName PlaceName;				// UI�� ������ �� ������ ����Ʈ ����
};


UCLASS()
class GAMEPROJECT_API ADialogueDataTable : public AActor
{
	GENERATED_BODY()
};