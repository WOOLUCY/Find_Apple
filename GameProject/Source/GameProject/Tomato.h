// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tomato.generated.h"

UCLASS()
class GAMEPROJECT_API ATomato : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATomato();
	UPROPERTY()
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Plant[3] ;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

private:
	int WaterCount;
	int level;
	//0,1,2������ �Ĺ��ܰ� 3,4,5�� ���Ŵܰ��� �� �� �� �ܰ���
	bool IsDead;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//�ð��ڵ� �޾ƿͼ� �ؾ߰���
	void ChangePlant();
	bool IsDeadCheck();
};
