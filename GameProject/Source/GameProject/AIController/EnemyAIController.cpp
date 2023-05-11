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
	
	// InPawn을 EnemyCharacter로 변환
	auto Char = Cast <AEnemyCharacter>(InPawn);
	// 포인터가 유효한지 검사
	if(Char && Char->EnemyBehaviorTree)
	{
		BlackboardComp->InitializeBlackboard(*Char->EnemyBehaviorTree->BlackboardAsset);
		TargetKeyID = BlackboardComp->GetKeyID("Target");
		BehaviorComp->StartTree(*Char->EnemyBehaviorTree);
	}
}
