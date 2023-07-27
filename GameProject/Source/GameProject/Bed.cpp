// Fill out your copyright notice in the Description page of Project Settings.


#include "Bed.h"

#include "Kismet/GameplayStatics.h"

#include "FindAppleGameMode.h"
#include "FindApplePlayerController.h"
#include "FindAppleCharacter.h"


#include "KaonWidget/SleepWidget.h"

#include <Engine/World.h>
#include <LevelSequenceActor.h>
#include <LevelSequencePlayer.h>
#include <MovieSceneSequencePlayer.h>
#include "Camera/CameraActor.h"
#include "Engine/LevelScriptActor.h"
#include "MainLevelScriptActor.h"


// Sets default values
ABed::ABed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Bed = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BED"));
	RootComponent = Bed;
	Bedding = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BEDDING"));
	Bedding->SetupAttachment(RootComponent);
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Box->SetupAttachment(RootComponent);

	Box->SetBoxExtent(FVector(125.f,100.f,100.f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BED
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/Bed.Bed'"));
	if (SM_BED.Succeeded()) {
		Bed->SetStaticMesh(SM_BED.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BEDINGE
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/bedding.bedding'"));

	if (SM_BEDINGE.Succeeded()) {
		Bedding->SetStaticMesh(SM_BEDINGE.Object);
		NotLaying = SM_BEDINGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BEDINGE_LAYING
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/bedding_charlaying.bedding_charlaying'"));
	if (SM_BEDINGE_LAYING.Succeeded()) {
		Laying = SM_BEDINGE_LAYING.Object;
	}

	Bed->SetCollisionProfileName("BlockAll");
	Bedding->SetCollisionProfileName("BlockAll");


	Box->SetCollisionProfileName("OverlapAll");


	//À§Á¬
	static ConstructorHelpers::FClassFinder<USleepWidget> SLEEP_WIDGET
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/kaon/UI/BedOverlap.BedOverlap_C'"));

	if (SLEEP_WIDGET.Succeeded()) {
		SleepWidgetClass = SLEEP_WIDGET.Class;
		UE_LOG(LogTemp, Warning, TEXT("sleep widget bind success"));
	}



	Box->OnComponentBeginOverlap.AddDynamic(this, &ABed::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &ABed::OnOverlapEnd);

	//Grab Music Sound
	static ConstructorHelpers::FObjectFinder<USoundWave> sleepSoundCue(TEXT("/Script/Engine.SoundWave'/Game/Semin/Sound/Sleep.Sleep'"));
	SleepAudioCue = sleepSoundCue.Object;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PropellerAudioComp"));
	AudioComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ABed::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> MatrixSequencs;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ALevelSequenceActor::StaticClass(), FName("Bed"), MatrixSequencs);

	for (AActor* Actor : MatrixSequencs)
	{
		SequenceCinematic = Cast<ALevelSequenceActor>(Actor);
	}
}


void ABed::PostInitializeComponents()
{
	Super::PostInitializeComponents();


	if (SleepAudioCue->IsValidLowLevelFast()) {
		AudioComponent->SetSound(SleepAudioCue);
	}

}


void ABed::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto hero = Cast<AFindAppleCharacter>(OtherActor);


	if (hero != nullptr) {
		ShowWdiget();
	}
	else {
		return;
	}
}

void ABed::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto hero = Cast<AFindAppleCharacter>(OtherActor);
	if (hero != nullptr) {
		HiddenWidget();
	}
	else {
		return;
	}
}

// Called every frame
void ABed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
                                    
void ABed::ShowWdiget()
{
	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr) {

		auto hero = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AFindApplePlayerController* MyContorller = Cast<AFindApplePlayerController>(hero);
		if (MyContorller != nullptr) {
			if (IsVisibleWidget == false)
			{
				SleepWdiget = CreateWidget<USleepWidget>(MyContorller, SleepWidgetClass);
				SleepWdiget->AddToViewport();
				IsVisibleWidget = true;
			}
			MyContorller->SetInputMode(FInputModeGameAndUI());
			MyContorller->bShowMouseCursor = true;


			SleepWdiget->YesDelegate.BindUObject(this, &ABed::YesChoice);
			SleepWdiget->NoDelegate.BindUObject(this, &ABed::NoChoice);


		}
	}




}
void ABed::HiddenWidget()
{

	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr) {

		auto hero = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AFindApplePlayerController* MyContorller = Cast<AFindApplePlayerController>(hero);
		if (MyContorller != nullptr) {
			if (IsVisibleWidget == true)
			{
				SleepWdiget->RemoveFromParent();
				IsVisibleWidget = false;
			}
			MyContorller->SetInputMode(FInputModeGameOnly());
			MyContorller->bShowMouseCursor = false;

			SleepWdiget->YesDelegate.Unbind();
			SleepWdiget->NoDelegate.Unbind();

		}
	}

}

void ABed::YesChoice()
{
	FString Name = "SleepLevel";
	//UGameplayStatics::OpenLevel(this, *Name);
	SequenceCinematic->SequencePlayer->Play();

	AMainLevelScriptActor* LevelScript = Cast<AMainLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	LevelScript->BackgroundMusicStopAndPlay();

	float startTime = 0.f;
	float volume = 0.8f;
	float fadeTime = 0.8f;
	AudioComponent->FadeIn(fadeTime, volume, startTime);
	AudioComponent->FadeOut(fadeTime, volume);

	AudioComponent->SetSound(SleepAudioCue);
	AudioComponent->Play();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			AudioComponent->Stop();

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), 4.f, false);

	HiddenWidget();
}

void ABed::NoChoice()
{
	HiddenWidget();
}

