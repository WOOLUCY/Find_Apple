// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLevelScriptActor.h"
#include "GameStartWidget.h"
#include "Kismet/GameplayStatics.h"

AStartLevelScriptActor::AStartLevelScriptActor()
{
	ConstructorHelpers::FClassFinder<UGameStartWidget>  GameStartWidgetObject(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/GameStart/GameStartWidget.GameStartWidget_C'"));
	if (GameStartWidgetObject.Succeeded())
	{
		GameStartWidgetClass = GameStartWidgetObject.Class;
	}
}

void AStartLevelScriptActor::BeginPlay()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	GameStartUIObject = CreateWidget<UGameStartWidget>(GetWorld(), GameStartWidgetClass);
	GameStartUIObject->AddToViewport();
	PlayerController->SetShowMouseCursor(true);
}
