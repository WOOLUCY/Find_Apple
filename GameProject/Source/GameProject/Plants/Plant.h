// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plant.generated.h"

UCLASS()
class GAMEPROJECT_API APlant : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlant();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;


	int LiveDay = 0;	//����ִ³�¥
	int WaterCount = 0; //���س�¥
	int MaxDeathDay=2;	//�����༭ �״³�¥
	int DeathCount = 0; //�����س�¥
	int NowLevel = 0;	//���缺��ܰ��� �Ĺ�
	int MaxLevel = 3;   //���� �ִ�ܰ�
	int LevelUp = 1;	//�����ϴ� ������ϴ� Ƚ��
	bool IsFruit = false;//�����ִ���������
	bool CanHarvest = false; //��Ȯ��ų���ִ��� �������� Ȯ��


	FName ItemName;


	TArray<UStaticMesh*> Meshs;

	UStaticMeshComponent* Current;

private:



	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PutWater();
	virtual bool Harvest();
	virtual void DayChange();

	

};
