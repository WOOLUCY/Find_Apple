// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NepenthesAttack.h"
#include "AIController.h"
#include "FindAppleCharacter.h"

UBTTask_NepenthesAttack::UBTTask_NepenthesAttack()
{
	NodeName = TEXT("NepenthesAttack");
}

EBTNodeResult::Type UBTTask_NepenthesAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	/* Attack Player */
	AFindAppleCharacter* MyChar = Cast<AFindAppleCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!MyChar->GetIsAttacked())	// If player can be attacked
	{
		// 체력을 변경
		//UE_LOG(LogClass, Warning, TEXT("Player Current HP: %f"), MyChar->GetCurHealth());

		UWorld* TheWorld = GetWorld();
		FDamageEvent DamageEvent;
		MyChar->TakeDamage(10.f, DamageEvent, UGameplayStatics::GetPlayerController(TheWorld, 0), nullptr);
	}


	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AFindAppleCharacter* Character = Cast<AFindAppleCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}


	Character->Action();

	return EBTNodeResult::Succeeded;
}
