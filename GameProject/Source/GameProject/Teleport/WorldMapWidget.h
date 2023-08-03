// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorldMapWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UWorldMapWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UWorldMapWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* NPChouse;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* FrontDungeon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Bridge;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Home;
	
	/* Black Screen Pop (어두워지는 효과) */
	/* Begin */
	UPROPERTY()
	TSubclassOf<class UUserWidget> BlackScreenBeginClass;
	UPROPERTY()
	class UBlackScreenBegin* BlackScreenBeginUIObject;

	/* Hover Action */
	UFUNCTION()
	void NPCHouseButtonHovered();
	UFUNCTION()
	void FrontDungeonButtonHovered();
	UFUNCTION()
	void HomeButtonHovered();
	UFUNCTION()
	void BridgeButtonHovered();
	/* Not Hover Action */
	UFUNCTION()
	void NPCHouseButtonNotHovered();
	UFUNCTION()
	void FrontDungeonButtonNotHovered();
	UFUNCTION()
	void HomeButtonNotHovered();
	UFUNCTION()
	void BridgeButtonNotHovered();
	/* Click Action */
	UFUNCTION()
	void NPCHouseButtonClick();
	UFUNCTION()
	void FrontDungeonButtonClick();
	UFUNCTION()
	void HomeButtonClick();
	UFUNCTION()
	void BridgeButtonClick();
	UFUNCTION()
	void Remove();

private:
	UFUNCTION()
	void TeleportPlayer(FName Place);
	UFUNCTION()
	void BlackScreenPopStart();
	UFUNCTION()
	void BlackScreenPopEnd();
};
