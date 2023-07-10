// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"
#include "../FindAppleCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"

void ASlimeAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void ASlimeAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(PlayerPawn);

	// AI�� �÷��̾ �߰��� �� �ִ� ������ 1000 ���� ������!!!
	if (LineOfSightTo(PlayerPawn) && GetPawn()->GetDistanceTo(PlayerPawn) < 1000 ) // 1000�� ������ ���� �κ�
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());

		// AI �� �÷��̾ �߰��ϸ� �������� �뷡 ���
		SetBattleMusicPlay();
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		
		// AI�� �þ߿��� ������� �������� �뷡 ����
		SetBattleMusicStop();
	}


}

void ASlimeAIController::SetBattleMusicPlay()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(PlayerPawn);


	if (firstSeeing == true)
	{
		MyCharacter->countOfMonstersAggro += 1;
		firstSeeing = false;
	}
}

void ASlimeAIController::SetBattleMusicStop()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(PlayerPawn);
	if (firstSeeing == false)
	{	
		MyCharacter->countOfMonstersAggro -= 1;
		firstSeeing = true;
	}
}
