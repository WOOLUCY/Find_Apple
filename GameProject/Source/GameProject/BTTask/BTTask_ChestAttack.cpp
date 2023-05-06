// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChestAttack.h"
#include "AIController.h"
#include "../FindAppleCharacter.h"
#include "Widgets/Text/ISlateEditableTextWidget.h"

UBTTask_ChestAttack::UBTTask_ChestAttack()
{
	NodeName = TEXT("ChestAttack");
}

EBTNodeResult::Type UBTTask_ChestAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	/* Attack Player */
	AFindAppleCharacter* MyChar = Cast<AFindAppleCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));


	// TODO: �ǰ� ��Ȳ �� �Ų����� ��ĥ ��
	if (!MyChar->GetIsAttacked())	// If player can be attacked
	{
		// ü���� ����
		UE_LOG(LogClass, Warning, TEXT("Player Current HP: %f"), MyChar->GetCurHealth());

		UWorld* TheWorld = GetWorld();
		FDamageEvent DamageEvent;

		MyChar->TakeDamage(25.f, DamageEvent, UGameplayStatics::GetPlayerController(TheWorld, 0), nullptr);
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
