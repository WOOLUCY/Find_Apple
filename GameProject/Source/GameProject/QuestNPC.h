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

	/* 카메라 블렌드 무브를 위한 함수 생성 */
	UFUNCTION()
	void PlayerAdjustmentss();

	/* 플레이어가 collised 상태에서 Q를 눌렀을 경우 인터페이스 */
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

	/* 타임 라인 */
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
	/* 타임 라인 */
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
	int32 NPC_ID = 500;			// 퀘스트 NPC ID 는 1 번

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

	/* 퀘스트 마지막 말에는 대화가 끝날 수 있도록하는 bool값 */
	UPROPERTY()
	bool QuestAccept = false;
	/* 퀘스트 리스트에 더하기용 불값 */
	UPROPERTY()
	bool SetQuestList = false;
};
