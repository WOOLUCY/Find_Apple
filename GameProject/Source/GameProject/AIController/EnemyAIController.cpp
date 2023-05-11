// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "../EnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemyAIController::AEnemyAIController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	// InPawn�� EnemyCharacter�� ��ȯ
	auto Char = Cast <AEnemyCharacter>(InPawn);
	// �����Ͱ� ��ȿ���� �˻�
	if(Char && Char->EnemyBehaviorTree)
	{
		BlackboardComp->InitializeBlackboard(*Char->EnemyBehaviorTree->BlackboardAsset);
		TargetKeyID = BlackboardComp->GetKeyID("Target");
		BehaviorComp->StartTree(*Char->EnemyBehaviorTree);
	}
}
