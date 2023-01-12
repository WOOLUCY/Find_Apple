// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "LevelTransferVol.generated.h"

UCLASS()
class GAMEPROJECT_API ALevelTransferVol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTransferVol();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	FString TransferLevelName;

	UPROPERTY()
	UBoxComponent* TransferVol;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
