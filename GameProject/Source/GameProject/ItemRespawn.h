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

	/* �������� �Ǵ� �ð� ���� ( ����: �� ) */
	UPROPERTY(EditAnywhere, Category = "Setting")
	float SecTimer = 5.f;
	
	/* �ش� ������ ������ �� ������ ���� */
	UPROPERTY(EditAnywhere, Category = "Setting")
	int RespawnNum = 20;

	/* ������ �������� �� �̸� */
	UPROPERTY(EditAnywhere, Category = "Setting")
	FName SpawnItemName = FName(TEXT("branch"));

private:
	UFUNCTION()
	void AdvanceTimer();
	UPROPERTY()
	FTimerHandle CountdownTimerHandle;
	/* ������ ������ �� �������� �ʵ��� Ȯ���ϴ� ���� */
	UFUNCTION()
	void CheckActors();
	UPROPERTY()
	//TArray<AActor*> Actors;
	TArray<TWeakObjectPtr<AActor>> Actors;
	/* ���� ������ �Լ� */
	UFUNCTION()
	void RespawnActor();
	UFUNCTION()
	void GetRandomPointInCollisionBox();

	/* �� ���� �ִ� 5 ���� ������ �� */
	UPROPERTY()
	int32 CurRespawnNum = 5;
};
