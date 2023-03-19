// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../FindAppleInterface.h"
#include "CraftingActor.generated.h"

UCLASS()
class GAMEPROJECT_API ACraftingActor : public AActor, public IFindAppleInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACraftingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* 플레이어가 collised 상태에서 Q를 눌렀을 경우 인터페이스 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnActivate(); virtual void OnActivate_Implementation() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionMesh = nullptr;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	/* Crafting Widget */
	UPROPERTY()
	TSubclassOf<class UUserWidget> CraftingAllWidgetClass;
	UPROPERTY()
	class UCraftingAllWidget* CraftingAllUIObject;

	/* Press E to Chat Widget */
	UPROPERTY()
	TSubclassOf<class UUserWidget> PressKeyWidgetClass;
	UPROPERTY()
	class UPressKeyWidget* PressKeyWidgetUIObejct;
	
	UPROPERTY()
	class UDataTable* ItemDataTable;
	TArray<struct FInventoryTableRow*> InventoryData;

	/* Is Widget Valid ? */
	UPROPERTY()
	bool bIsPressKeyValid = false;
	UPROPERTY()
	bool bIsWidgetValid = false;
};
