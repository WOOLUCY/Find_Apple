// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLevelScriptActor.h"
#include "GameStartWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"

AStartLevelScriptActor::AStartLevelScriptActor()
{
	ConstructorHelpers::FClassFinder<UGameStartWidget>  GameStartWidgetObject(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/GameStart/GameStartWidget.GameStartWidget_C'"));
	if (GameStartWidgetObject.Succeeded())
	{
		GameStartWidgetClass = GameStartWidgetObject.Class;
	}

	//SoundCue 사용 방법
    static ConstructorHelpers::FObjectFinder<USoundWave> propellerCue(TEXT("/Script/Engine.SoundWave'/Game/Semin/Sound/GameStart.GameStart'"));
    backgoundMusicAudioCue = propellerCue.Object;

	backgoundMusicAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PropellerAudioComp"));
	backgoundMusicAudioComponent->bAutoActivate = false;
}

void AStartLevelScriptActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (backgoundMusicAudioCue->IsValidLowLevelFast()) {
		backgoundMusicAudioComponent->SetSound(backgoundMusicAudioCue);
	}
}

void AStartLevelScriptActor::BeginPlay()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	GameStartUIObject = CreateWidget<UGameStartWidget>(GetWorld(), GameStartWidgetClass);
	GameStartUIObject->AddToViewport();
	PlayerController->SetShowMouseCursor(true);


	float startTime = 9.f;
	float volume = 1.0f;
	float fadeTime = 1.0f;
	backgoundMusicAudioComponent->FadeIn(fadeTime, volume, startTime);

	backgoundMusicAudioComponent->Play();
}
