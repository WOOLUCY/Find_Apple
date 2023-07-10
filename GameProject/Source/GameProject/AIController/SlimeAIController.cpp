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

	// AI가 플레이어를 발견할 수 있는 범위를 1000 으로 제한함!!!
	if (LineOfSightTo(PlayerPawn) && GetPawn()->GetDistanceTo(PlayerPawn) < 1000 ) // 1000의 조건을 넣은 부분
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());

		// AI 가 플레이어를 발견하면 위협적인 노래 재생
		SetBattleMusicPlay();
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		
		// AI가 시야에서 사라지면 위협적인 노래 중지
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
