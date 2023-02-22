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

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UMaterialInstance* MDay;
	UMaterialInstance* MNight;

	bool IsNight = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Sunset();
	void Sunrise();

};
