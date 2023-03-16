// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Sword.h"
#include "Pick.h"
#include "Ax.h"


#include "FindAppleCharacter.generated.h"

class UInputMappingContext;
class UInputAction;


UCLASS()
class GAMEPROJECT_API AFindAppleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFindAppleCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* CharacterMappingContext;

	/* input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveForwardAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveRightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* QuestInteractionAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InventoryAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* PickItemAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MouseToggleAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* WorldMapAction;

	//가온 - 도구선택, 대쉬
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* DashMapping;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* SwordMapping;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* AxMapping;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* PickMapping;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* ResetEquipMapping;



	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void QuestInteraction(const FInputActionValue& Value);
	void Inventory(const FInputActionValue& Value);
	void PickItem(const FInputActionValue& Value);
	void MouseToggle(const FInputActionValue& Value);
	void ShowWorldMap(const FInputActionValue& Value);

	void EquipSword(const FInputActionValue& Value);
	void EquipAx(const FInputActionValue& Value);
	void EquipPick(const FInputActionValue& Value);
	void EquipReset(const FInputActionValue& Value);
	void ChangeSpeed(const FInputActionValue& Value);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Action();
	void DayChange();

	FDelegateHandle MyDelegateHandle;

	
	UFUNCTION()
	void OnActionMontageEnded(UAnimMontage* Montage, bool bInteruppted);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* CameraComponent;


	/* Inventory Widget Class */
	UPROPERTY()
	TSubclassOf<class UUserWidget> InventoryWidgetClass;
	UPROPERTY()
	class UInventoryUW* InventoryUIObject;
	UPROPERTY()
	bool bInventoryWidget = false;
	
	/* Item Pick up Check */
	UPROPERTY()
	bool PressE = false;
	UPROPERTY()
	AActor* LookAtActorPressE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UInventoryComponent* InventoryComponent;
	UPROPERTY()
	bool HideToolTip = true;

	/* Quest System */
	UPROPERTY()
	TSubclassOf<class UUserWidget> QuestListWidgetClass;
	UPROPERTY()
	class UQuestListWidget* QuestListUIObject;
	UPROPERTY()
	int32 QuestNum = 0; 

	/* World Map Widget Class */
	UPROPERTY()
	TSubclassOf<class UUserWidget> WorldMapWidgetClass;
	UPROPERTY()
	class UWorldMapWidget* WorldMapUIObject;
	UPROPERTY()
	bool bWorldMapWidget = false;



	/* Combat */
	//UPROPERTY(EditAnywhere, Category = "Combat")
	//bool IsAttacking = false;
	float GetCurHealth() { return CurHealth; }
	void SetCurHealth(float _health) { CurHealth = _health; }
	int32 GetEquipNum() { return CurEquipNum; }

	/* Post Process Effect */
	UPROPERTY(EditAnywhere, Category = "PostProcessMaterial")
	class UPostProcessComponent* PostProcessComp;


	/* Camera Shake */
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase>  HitCameraShakeClass;



private:
	// HUD에서 사용해야 돼가지고, private에서 public으로 뺐습니다.
	UPROPERTY(VisibleAnywhere)
		float CurHealth;

	UPROPERTY(VisibleAnywhere)
		int32 CurEquipNum;

	UPROPERTY(VisibleAnywhere)
		AActor* CurEquipActor;


	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	float CameraRotationRate = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 200;



	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAction;

	UPROPERTY()
	class UFindAppleAnimInstance* Anim;


};
