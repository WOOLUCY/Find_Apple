// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TeleportNameWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UTeleportNameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UTeleportNameWidget(const FObjectInitializer& objectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlaceText;
};
