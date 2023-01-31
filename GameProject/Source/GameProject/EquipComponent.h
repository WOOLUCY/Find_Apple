// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FindAppleAnimInstance.h"
#include "EquipComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROJECT_API UEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipComponent();

	UPROPERTY(VisibleAnywhere)
		float Damage;

	UPROPERTY(VisibleAnywhere)
		bool IsCollide;

	void SetDamage(float SetDam);

	UFUNCTION()
	void CollideCheck();

	UPROPERTY()
		UFindAppleAnimInstance* Anim;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
