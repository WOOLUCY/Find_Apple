// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "LevelTransferVol.generated.h"

UCLASS()
class GAMEPROJECT_API ALevelTransferVol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTransferVol();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UDoorWidget> DoorWidgetClass;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString TransferLevelName;

	UPROPERTY()
	UBoxComponent* TransferVol;

	UPROPERTY()
	FName TeleportPointName;


	UPROPERTY()
	class UDoorWidget* DoorWdiget;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ShowWdiget();
	void HiddenWidget();

	void YesChoice();
	void NoChoice();

	void MovePointAtTeleport();
	void BlackScreenEndAnim();

	bool IsVisibleWidget = false;
};
