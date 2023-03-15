// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"
#include "FindAppleCharacter.h"
#include "Widgets/Text/ISlateEditableTextWidget.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	/* Attack Player */
	AFindAppleCharacter* MyChar = Cast<AFindAppleCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// TODO: �ǰ� ��Ȳ �� �Ų����� ��ĥ ��
	MyChar->CurHealth -= 20.f;	// damage
	UE_LOG(LogClass, Warning, TEXT("Enemy Is Attacking"));
	UE_LOG(LogClass, Warning, TEXT("Player Current HP: %f"), MyChar->CurHealth);

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
