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

	// TODO: 피격 상황 더 매끄럽게 고칠 것
	if(MyChar->HitCameraShakeClass)
	{
		// Camera Shake
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(MyChar->HitCameraShakeClass);
	}

	float NewHealth = MyChar->GetCurHealth();
	NewHealth -= 20.f;
	MyChar->SetCurHealth(NewHealth);
	UE_LOG(LogClass, Warning, TEXT("Enemy Is Attacking"));
	UE_LOG(LogClass, Warning, TEXT("Player Current HP: %f"), NewHealth);


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
