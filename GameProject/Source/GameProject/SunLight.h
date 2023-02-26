// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/DirectionalLightComponent.h"

#include "SunLight.generated.h"

UCLASS()
class GAMEPROJECT_API ASunLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASunLight();

	UPROPERTY(EditAnywhere)
		UDirectionalLightComponent* Sun;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Sky;

	UPROPERTY(EditAnywhere)
		bool IsNight = false;



	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UMaterialInstance* MDay;
	UMaterialInstance* MNight;

	const FRotator BasicRot{ 0,180.f,180.f };
	const FColor BlueColor{ 73,101,179,255 };
	const FColor PurpeColor{ 187,86,255,255 };
	


	//UPROPERTY(EditAnywhere)
	//bool IsNight = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Sunrise();


	void SetNight();

	class ATimerHandler* GameTimer;



};
