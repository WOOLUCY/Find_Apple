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
	//0,1,2까지가 식물단계 3,4,5가 열매단계임 초 핑 빨 단계임
	bool IsDead;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//시간핸들 받아와서 해야겠음
	void ChangePlant();
	bool IsDeadCheck();
};
