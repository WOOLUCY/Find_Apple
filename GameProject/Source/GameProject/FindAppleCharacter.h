// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Sword.h"
#include "Pick.h"
#include "Ax.h"
#include "DoOnce.h"


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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SkipAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TeleportAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* QuestTeleportAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TeleportQuestNPCAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TeleportTreeAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TeleportDungeonAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TeleportHouseAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TeleportCaveAction;

	// W: Pause Menu
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* PauseAction;

	// W: Wheel Tool
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* WheelUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* WheelDownAction;

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
	void ShowPauseMenu(const FInputActionValue& Value);
	void SkipQuest(const FInputActionValue& Value);
	void Teleport(const FInputActionValue& Value);
	void TeleportAtQuestNPCAction(const FInputActionValue& Value);
	void TeleportQuestNPC(const FInputActionValue& Value);
	void TeleportTree(const FInputActionValue& Value);
	void TeleportDungeon(const FInputActionValue& Value);
	void TeleportHouse(const FInputActionValue& Value);
	void TeleportCave(const FInputActionValue& Value);

	void EquipSword(const FInputActionValue& Value);
	void EquipAx(const FInputActionValue& Value);
	void EquipPick(const FInputActionValue& Value);
	void EquipReset(const FInputActionValue& Value);
	void ChangeSpeed(const FInputActionValue& Value);

	void UpEquip(const FInputActionValue& Value);
	void DownEquip(const FInputActionValue& Value);


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



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* ItemDataTable;

	TArray<struct FInventoryTableRow*> InventoryData;


	/* Quest System */
	//UPROPERTY()
	//TSubclassOf<class UUserWidget> QuestListWidgetClass;
	//UPROPERTY()
	//class UQuestListWidget* QuestListUIObject;
	//UPROPERTY()
	//int32 QuestNum = 0; 
	UPROPERTY()
	FName Place;

	/* World Map Widget Class */
	UPROPERTY()
	TSubclassOf<class UUserWidget> WorldMapWidgetClass;
	UPROPERTY()
	class UWorldMapWidget* WorldMapUIObject;
	UPROPERTY()
	bool bWorldMapWidget = false;

	/* PauseMenu Widget Class */
	UPROPERTY()
	TSubclassOf<class UUserWidget> PauseWidgetClass;
	UPROPERTY()
	class UPauseWidget* PauseUIObject;
	UPROPERTY()
	bool bPauseWidget = false;

	/* Post Process Effect */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PostProcessMaterial")
	class UPostProcessComponent* PostProcessComp;

	/* Camera Shake */
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase>  HitCameraShakeClass;

	/* Hunger */
	float GetCurHunger() { return CurHunger; }
	void SetCurHunger(float _hunger) { CurHunger = _hunger; }
	float GetMaxHunger() { return MaxHunger; }

	/* Combat */
	//UPROPERTY(EditAnywhere, Category = "Combat")
	//bool IsAttacking = false;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void DamageReaction(float DamageAmount);
	FDoOnce DoOnce;


	/* Gettor & Settor */
	float GetCurHealth() { return CurHealth; }
	void SetCurHealth(float _health) { CurHealth = _health; }
	float GetMaxHealth() { return MaxHealth; }
	int32 GetEquipNum() { return CurEquipNum; }
	void SetEquipNum(int in) { CurEquipNum = in; }
	void ChangeEquipment(int in);

	bool GetIsAttacked() { return bIsAttacked; }
	void SetIsAttacked(bool _in) { bIsAttacked = _in; }
	bool GetIsAttacking() { return bIsAttacking; }
	void SetIsAttacking(bool _in) { bIsAttacking = _in; }

	bool GetIsRunning() { return bIsRunning; }
	void SetIsRunning(bool _in) { bIsRunning = _in; }
	
	
public:
	UFUNCTION()
	void BlackScreenPopStart();
	UFUNCTION()
	void BlackScreenPopEnd();
	/* Black Screen Pop (어두워지는 효과) */
	/* Begin */
	UPROPERTY()
	TSubclassOf<class UUserWidget> BlackScreenBeginClass;
	UPROPERTY()
	class UBlackScreenBegin* BlackScreenBeginUIObject;
	UPROPERTY()
	FVector MoveLocation;
	UPROPERTY()
	FRotator MoveRotation;


private:
	UPROPERTY()
	FName TeleportPointName;
	UFUNCTION()
	void MovePointAtTeleport();

	UPROPERTY(VisibleAnywhere)
		bool bIsRunning;

	/* Combat */
	UPROPERTY(VisibleAnywhere)
		bool bIsAttacked;

	UPROPERTY(VisibleAnywhere)
		bool bIsAttacking;

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

	// Hunger
	UPROPERTY(EditDefaultsOnly)
	float MaxHunger = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float CurHunger;


	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAction;

	UPROPERTY()
	class UFindAppleAnimInstance* Anim;

	//Semin
	bool isEquipOwn = false;

};

