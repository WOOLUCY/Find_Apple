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
	if (!MyChar->GetIsAttacked())	// If player can be attacked
	{
		// 피격 상태 변환 -> 캐릭터에서 할 것
		//MyChar->SetIsAttacked(true);

		// 카메라 쉐이크
		if (MyChar->HitCameraShakeClass)
		{
			// Camera Shake
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(MyChar->HitCameraShakeClass);
		}

		// 체력을 변경
		//float NewHealth = MyChar->GetCurHealth();
		UWorld* TheWorld = GetWorld();
		FDamageEvent DamageEvent;
		MyChar->TakeDamage(20.f, DamageEvent, UGameplayStatics::GetPlayerController(TheWorld, 0), nullptr);
		//NewHealth -= 20.f;
		//MyChar->SetCurHealth(NewHealth);

		// log
		//UE_LOG(LogClass, Warning, TEXT("Enemy Is Attacking"));
		//UE_LOG(LogClass, Warning, TEXT("Player Current HP: %f"), NewHealth);

		// 일정 시간 후 다시 피격 가능 상태로 변환
		//FTimerHandle Timer;
		//float WaitTime = 5.f;

		//GetWorld()->GetTimerManager().SetTimer(Timer, FTimerDelegate::CreateLambda([&]()
		//	{
		//		MyChar->SetIsAttacked(false);
		//		//GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		//	}), WaitTime, false);
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
