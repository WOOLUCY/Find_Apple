// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "Bed.generated.h"

UCLASS()
class GAMEPROJECT_API ABed : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABed();

	UStaticMeshComponent* Bed;
	UStaticMeshComponent* Bedding;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class USleepWidget> SleepWidgetClass;

	UPROPERTY(VisibleAnywhere)
	class ALevelSequenceActor* SequenceCinematic;
	UPROPERTY(VisibleAnywhere)
	class ACameraActor* BedCamera;

	bool IsVisibleWidget = false;



private:
	UStaticMesh* Laying;
	UStaticMesh* NotLaying;

	UPROPERTY()
		class USleepWidget* SleepWdiget;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ShowWdiget();
	void HiddenWidget();

	void YesChoice();
	void NoChoice();
	
	//Pick sound
	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundWave* SleepAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class UAudioComponent* AudioComponent;
};
