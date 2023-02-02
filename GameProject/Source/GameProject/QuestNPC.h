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

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UTextRenderComponent* Text;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MyCone = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components")
	int32 NPC_ID = 500;			// ����Ʈ NPC ID �� 1 ��

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
