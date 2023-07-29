// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "FishingVol.generated.h"

UCLASS()
class GAMEPROJECT_API AFishingVol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFishingVol();


private:
	UPROPERTY()
	UBoxComponent* FishginVolumeBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
