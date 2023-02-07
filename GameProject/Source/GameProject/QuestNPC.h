// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FindAppleInterface.h"
#include "Components/TimelineComponent.h"
#include "QuestNPC.generated.h"

UCLASS()
class GAMEPROJECT_API AQuestNPC : public ACharacter, public IFindAppleInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQuestNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	TArray<struct FDialogueTableRow*> DialogueData;

	/* ī�޶� ���� ���긦 ���� �Լ� ���� */
	UFUNCTION()
	void PlayerAdjustmentss();

	/* �÷��̾ collised ���¿��� Q�� ������ ��� �������̽� */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnActivate(); virtual void OnActivate_Implementation() override;

	UFUNCTION()
	void DialogueCreate();

	UFUNCTION()
	void DialogueGetLine();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/* widget class */
	UPROPERTY()
	TSubclassOf<class UUserWidget> DialogueWidgetClass;

	UPROPERTY()
	TSubclassOf<class UUserWidget> DialoguePopWidgetClass;

	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* CameraComponent;

	/* Ÿ�� ���� */
	UFUNCTION()
	void TimelineProgress(float Value);
	UFUNCTION()
	void TimelineFinished();

	UPROPERTY()
	TMap<FName, int32> QuestRequirItem;

	UPROPERTY()
	class UTextRenderComponent* Text;

	UPROPERTY(EditAnywhere, Category = "Components")
	int32 Conversation_ID = 0;

	UPROPERTY(EditAnywhere, Category = "Components")
	int32 CurrentLine = 0;

private:	
	/* Ÿ�� ���� */
	FTimeline CurveFTimeline;
	UPROPERTY(EditAnywhere, Category = "Components")
	UCurveFloat* CurveFloat;

	UPROPERTY()
	FVector StartLoc;
	UPROPERTY()
	FVector EndLoc;

	UPROPERTY()
	FRotator StartRot;
	UPROPERTY()
	FRotator EndRot;

	UPROPERTY()
	float ZOffset = 100;

	UPROPERTY()
	class UBoxComponent* CollisionMesh = nullptr;

	UPROPERTY()
	class UStaticMeshComponent* MyCone = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components")
	int32 NPC_ID = 500;			// ����Ʈ NPC ID �� 1 ��

	UPROPERTY()
	FText MyNameText;

	/* Is Dialogue Widget Valid */
	UPROPERTY()
	bool bIsValid = false;
	/* Is Press Key Widget Valid */
	UPROPERTY()
	bool bIsPressKeyValid = false;

	UPROPERTY()
	FTransform	CameraTransform;


	UPROPERTY()
	TArray<FName> MyDialogue;

	/* Dialouge Widget */
	UPROPERTY()
	class UDialogueWidget* DialogueUIObject;
	UPROPERTY()
	class UUserWidget* DialoguePopWidget;

	/* Press E to Chat Widget */
	UPROPERTY()
	TSubclassOf<class UUserWidget> PressKeyWidgetClass;
	UPROPERTY()
	class UUserWidget* PressKeyWidgetUIObejct;

	UPROPERTY()
	class UDataTable* DialogueDatatable;
	
	class AFindAppleGameMode* FAGameMode;

	/* Quest System */
	UPROPERTY()
	TSubclassOf<class UUserWidget> QuestListTextWidgetClass;
	UPROPERTY()
	class UQuestListTextWidget* QuestListTextUIObject;

	UPROPERTY()
	class UDataTable* ItemDataTable;
	TArray<struct FInventoryTableRow*> InventoryData;

	/* ����Ʈ ������ ������ ��ȭ�� ���� �� �ֵ����ϴ� bool�� */
	UPROPERTY()
	bool QuestAccept = false;
	/* ����Ʈ ����Ʈ�� ���ϱ�� �Ұ� */
	UPROPERTY()
	bool SetQuestList = false;
};
