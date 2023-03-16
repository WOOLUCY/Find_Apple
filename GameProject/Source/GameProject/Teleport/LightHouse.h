// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../FindAppleInterface.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "LightHouse.generated.h"

UCLASS()
class GAMEPROJECT_API ALightHouse : public AActor, public IFindAppleInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightHouse();

	/* �÷��̾ collised ���¿��� Q�� ������ ��� �������̽� */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnActivate(); virtual void OnActivate_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FText displayName;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* LightHouseMesh = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultRoot = nullptr;

	UPROPERTY()
	bool isPressed = false;
	UPROPERTY()
	bool isKeyWidget = false;

	/* Ÿ�� ���� */
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
	/* Ÿ�� ���� */
	FTimeline CurveFTimeline;
	UPROPERTY(EditAnywhere, Category = "Components")
	UCurveFloat* CurveFloat;

	// Camera
	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* FirstCameraComponent;
	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* SecondCameraComponent;

	// Box collision
	UPROPERTY()
	class UBoxComponent* CollisionMesh = nullptr;

	TSubclassOf<class UUserWidget> MapNameWidgetClass;
	class UShowMapNameWidget* MapNameWidgetUIObject;

	TSubclassOf<class UUserWidget> PressKeyClass;
	class UUserWidget* PressKeyUIObject;

	TSubclassOf<class UUserWidget> AddToMapWidgetClass;
	class UAddMapWidget* AddToMapWidgetUIObject;

	UPROPERTY()
	bool inves = false;	
	// ���� inves �� true ��� ������ �� ��'��'�� ǥ��
	// false ��� �ٸ� �� ���'��'�� ǥ��

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
