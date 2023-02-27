// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Bed.generated.h"

UCLASS()
class GAMEPROJECT_API ABed : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABed();

	UStaticMeshComponent* Bed;
	UStaticMeshComponent* Bedding;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* Box;

private:
	UStaticMesh* Laying;
	UStaticMesh* NotLaying;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
