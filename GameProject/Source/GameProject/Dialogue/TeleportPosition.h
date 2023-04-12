// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../FindAppleInterface.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "TeleportPosition.generated.h"

UCLASS()
class GAMEPROJECT_API ATeleportPosition : public AActor, public IFindAppleInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportPosition();

	/* 플레이어가 collised 상태에서 Q를 눌렀을 경우 인터페이스 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnActivate(); virtual void OnActivate_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultRoot = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* 타임 라인 */
	UFUNCTION()
	void TimelineProgress(float Value);
	UFUNCTION()
	void TimelineFinished();

	UPROPERTY()
	FVector StartLoc;
	UPROPERTY()
	FVector EndLoc;

	UPROPERTY()
	FRotator StartRot;
	UPROPERTY()
	FRotator EndRot;


private:
	/* 타임 라인 */
	FTimeline CurveFTimeline;
	UPROPERTY(EditAnywhere, Category = "Components")
	UCurveFloat* CurveFloat;



};
