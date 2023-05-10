// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
private:
	// AI ������Ʈ ������
	UBehaviorTreeComponent* BehaviorComp;
	UBlackboardComponent* BlackboardComp;
public:
	AEnemyAIController();

	// ��Ʈ�ѷ��� Pawn/Character�� ������ �� ȣ���
	virtual void OnPossess(APawn* InPawn) override;

	FBlackboard::FKey TargetKeyID;
};
