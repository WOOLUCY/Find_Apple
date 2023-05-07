// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "../FindAppleAnimInstance.h"

#include "Cloud.h"
#include "PlantWidget.h"

#include "FarmGround.generated.h"

UCLASS()
class GAMEPROJECT_API AFarmGround : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFarmGround();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* CheckMesh;
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere)
		UMaterial* Wet;
	UPROPERTY(VisibleAnywhere)
		UMaterial* NotWet;
	UPROPERTY(VisibleAnywhere)
		UMaterial* Overlap;

	UPROPERTY(VisibleAnywhere)
		AActor* cloud;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UPlantWidget> PlantWidgetClass;

	FDelegateHandle MyDelegateHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* ItemDataTable;

private:
	UPROPERTY()
		class UPlantWidget* PlantWdiget;


	class APlant* Planted;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY()
		UFindAppleAnimInstance* Anim;


private:
	bool IsEmpty;
	bool CanPutSeed;
	bool IsWet;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	void ShowPlantWidget();
	void HiddenPlantWidget();

	void DayChange();
	
	UFUNCTION()
	void PutWater();
	UFUNCTION()
	void PutSeed();
	UFUNCTION()
	void Harvest();

};
