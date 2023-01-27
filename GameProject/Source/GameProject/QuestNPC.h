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
	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class UUserWidget> DialogueWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<class UUserWidget> DialoguePopWidgetClass;

	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* CameraComponent;

	/* 타임 라인 */
	UFUNCTION()
	void TimelineProgress(float Value);
	UFUNCTION()
	void TimelineFinished();

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

	UPROPERTY(EditAnywhere, Category = "Components")
	float ZOffset;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UTextRenderComponent* Text;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MyCone = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components")
	int32 NPC_ID = 500;			// 퀘스트 NPC ID 는 1 번

	UPROPERTY(EditAnywhere, Category = "Components")
	int32 Conversation_ID = 0;

	UPROPERTY(EditAnywhere, Category = "Components")
	int32 CurrentLine = 0;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	FText MyNameText;

	UPROPERTY()
	bool bIsValid = false;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	FTransform	CameraTransform;


	UPROPERTY()
	TArray<FName> MyDialogue;

	UPROPERTY()
	class UDialogueWidget* DialogueUIObject;
	UPROPERTY()
	class UUserWidget* DialoguePopWidget;

	UPROPERTY()
	class UDataTable* DialogueDatatable;
	
	class AFindAppleGameMode* FAGameMode;

};
