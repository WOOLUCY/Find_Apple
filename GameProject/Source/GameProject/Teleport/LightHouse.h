// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "../FindAppleInterface.h"

#include "LightHouse.generated.h"

UCLASS()
class GAMEPROJECT_API ALightHouse : public AActor, public IFindAppleInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightHouse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/* 플레이어가 collised 상태에서 Q를 눌렀을 경우 인터페이스 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Components")
	void OnActivate(); virtual void OnActivate_Implementation() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/* Press Key Widget */
	UPROPERTY()
	TSubclassOf<class UUserWidget> PressKeyWidgetClass;
	UPROPERTY()
	class UUserWidget* PressKeyWidgetUIObejct;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* StartCameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* EndCameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* LightHouseMesh = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultRoot = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* CollisionMesh = nullptr;

	/* 발견되었는지 */
	UPROPERTY()
	bool IsValid = false;

	
	/* 타임 라인 */
	UFUNCTION()
	void TimelineProgress(float Value);
	UFUNCTION()
	void TimelineFinished();
	FVector StartLoc;
	FVector EndLoc;
	FRotator StartRot;
	FRotator EndRot;

private:
	/* 타임 라인 */
	FTimeline CurveFTimeline;
	UPROPERTY(EditAnywhere, Category = "Components")
	UCurveFloat* CurveFloat;
};
