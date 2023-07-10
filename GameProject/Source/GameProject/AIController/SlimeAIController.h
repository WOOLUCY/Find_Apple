// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SlimeAIController.generated.h"


/**
 * 
 */
UCLASS()
class GAMEPROJECT_API ASlimeAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		//float AcceptanceRadius = 200;
		class UBehaviorTree* AIBehavior;
	UPROPERTY()
	bool firstSeeing = true;

	UFUNCTION()
	void SetBattleMusicPlay();
	UFUNCTION()
	void SetBattleMusicStop();
};
