// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../FindAppleInterface.h"
#include "GameFramework/Actor.h"
#include "DropedItem.generated.h"

UCLASS()
class GAMEPROJECT_API ADropedItem : public AActor, public IFindAppleInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropedItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<struct FInventoryTableRow*> InventoryData;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	/* �÷��̾ collised ���¿��� E �� ������ ��� �������̽� */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void PicUpItem(); virtual void PicUpItem_Implementation() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MyBox = nullptr;

	UPROPERTY(EditAnywhere, Category = "ItemSetting")
	class UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, Category ="ItemSetting")
	FName ItemName = "apple";
};
