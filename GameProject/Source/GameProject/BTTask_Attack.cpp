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
	if (!MyChar->GetIsAttacked())	// If player can be attacked
	{
		// �ǰ� ���� ��ȯ -> ĳ���Ϳ��� �� ��
		//MyChar->SetIsAttacked(true);

		// ī�޶� ����ũ
		if (MyChar->HitCameraShakeClass)
		{
			// Camera Shake
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(MyChar->HitCameraShakeClass);
		}

		// ü���� ����
		//float NewHealth = MyChar->GetCurHealth();
		UWorld* TheWorld = GetWorld();
		FDamageEvent DamageEvent;
		MyChar->TakeDamage(20.f, DamageEvent, UGameplayStatics::GetPlayerController(TheWorld, 0), nullptr);
		//NewHealth -= 20.f;
		//MyChar->SetCurHealth(NewHealth);

		// log
		//UE_LOG(LogClass, Warning, TEXT("Enemy Is Attacking"));
		//UE_LOG(LogClass, Warning, TEXT("Player Current HP: %f"), NewHealth);

		// ���� �ð� �� �ٽ� �ǰ� ���� ���·� ��ȯ
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
