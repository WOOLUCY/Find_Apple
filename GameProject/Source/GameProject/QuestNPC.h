// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FindAppleInterface.h"
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

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnActivate(); virtual void OnActivate_Implementation() override;

	void DialogueCreate();

	void DialogueGetLine();

private:	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> DialogueWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USkeletalMeshComponent* SKMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* CollisionMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components")
	int32 NPC_ID = 1;			// Äù½ºÆ® NPC ID ´Â 1 ¹ø

	UPROPERTY(VisibleAnywhere, Category = "Components")
	int32 Conversation_ID = 1;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	int32 CurrentLine = 0;

	UPROPERTY()
	TArray<FName> MyDialogue;




	UPROPERTY()
	class UDataTable* DialogueDatatable;
	
	class AFindAppleGameMode* FAGameMode;

};
