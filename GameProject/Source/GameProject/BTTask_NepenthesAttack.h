// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_NepenthesAttack.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UBTTask_NepenthesAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_NepenthesAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
