// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemRespawn.generated.h"

UCLASS()
class GAMEPROJECT_API AItemRespawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemRespawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* CollisionMesh = nullptr;

	/* 리스폰이 되는 시간 설정 ( 단위: 초 ) */
	UPROPERTY(EditAnywhere, Category = "Setting")
	float SecTimer = 5.f;
	
	/* 해당 구역에 리스폰 될 액터의 개수 */
	UPROPERTY(EditAnywhere, Category = "Setting")
	int RespawnNum = 20;

	/* 스폰할 아이템의 행 이름 */
	UPROPERTY(EditAnywhere, Category = "Setting")
	FName SpawnItemName = FName(TEXT("branch"));

private:
	UFUNCTION()
	void AdvanceTimer();
	UPROPERTY()
	FTimerHandle CountdownTimerHandle;
	/* 액터의 개수가 더 많아지지 않도록 확인하는 역할 */
	UFUNCTION()
	void CheckActors();
	UPROPERTY()
	//TArray<AActor*> Actors;
	TArray<TWeakObjectPtr<AActor>> Actors;
	/* 액터 리스폰 함수 */
	UFUNCTION()
	void RespawnActor();
	UFUNCTION()
	void GetRandomPointInCollisionBox();

	/* 한 번에 최대 5 개만 리스폰 됨 */
	UPROPERTY()
	int32 CurRespawnNum = 5;
};
