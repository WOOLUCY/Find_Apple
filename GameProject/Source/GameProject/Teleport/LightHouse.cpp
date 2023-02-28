// Fill out your copyright notice in the Description page of Project Settings.


#include "LightHouse.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"
#include "Blueprint/UserWidget.h"
#include "../FindAppleCharacter.h"

/* -------------------------------------------------------------------------- */
// 스폰 지점으로 지정하고 싶으면 배치한 액터에 "태그"를 추가해야 한다.
// 
// 다리 앞 등대 - Bridge
// NPC 집 옆 등대 - NPChouse
// 던전 쪽 등대 - FrontDungeon
/* -------------------------------------------------------------------------- */


// Sets default values
ALightHouse::ALightHouse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);

	LightHouseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightHouse"));
	LightHouseMesh->SetupAttachment(DefaultRoot);

	/* Box Static Mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Script/Engine.StaticMesh'/Game/Semin/Asset/LightHouse/LightHouse.LightHouse'"));
	if (Mesh.Succeeded())
	{
		LightHouseMesh->SetStaticMesh(Mesh.Object);
		LightHouseMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		LightHouseMesh->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
	}

	/* Collision Mesh */
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionMesh->SetBoxExtent(FVector(64.f, 64.f, 64.f));
	CollisionMesh->SetupAttachment(GetRootComponent());
	CollisionMesh->SetRelativeLocation(FVector(320.f, 0.f, 64.f));
	CollisionMesh->SetHiddenInGame(true);

	/* Camera */
	StartCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Start Camera"));
	StartCameraComponent->SetupAttachment(GetRootComponent());
	//CameraComponent->bUsePawnControlRotation = false;
	StartCameraComponent->SetRelativeLocationAndRotation(FVector(2.665514f, 493.564828f, 669.388877f), FRotator(-14.941587f, -49.824560f, -1.337803f));
	
	EndCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("End Camera"));
	EndCameraComponent->SetupAttachment(GetRootComponent());
	//CameraComponent->bUsePawnControlRotation = false;
	EndCameraComponent->SetRelativeLocationAndRotation(FVector(2.665514f, 173.564828f, 669.388877f), FRotator(-14.941587f, 25.175439, -1.337803));


	/* Press key Widget */
	ConstructorHelpers::FClassFinder<UUserWidget>  PressKeyWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_PressQ.WBP_PressQ_C'"));
	if (PressKeyWidget.Succeeded())
	{
		PressKeyWidgetClass = PressKeyWidget.Class;
	}

	/* TimeLine */
	ConstructorHelpers::FObjectFinder<UCurveFloat>  CurveObject(TEXT("/Script/Engine.CurveFloat'/Game/Semin/UI/Map/TimelineCurve.TimelineCurve'"));
	if (CurveObject.Succeeded())
	{
		CurveFloat = CurveObject.Object;
	}
}

// Called when the game starts or when spawned
void ALightHouse::BeginPlay()
{
	Super::BeginPlay();


	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ALightHouse::OnOverlapBegin);
	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &ALightHouse::OnOverlapEnd);
}

void ALightHouse::OnActivate_Implementation()
{
	PrimaryActorTick.bCanEverTick = true;

	if (IsValid == false)
	{
		PressKeyWidgetUIObejct->RemoveFromParent();
		AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		MyCharacter->GetCharacterMovement()->DisableMovement();
		MyCharacter->GetCharacterMovement()->Velocity = FVector(0.f, 0.f, 0.f);
		PlayerController->SetInputMode(FInputModeGameAndUI());

		PlayerController->SetViewTargetWithBlend(StartCameraComponent->GetOwner(), 2.5f);

		FTimerHandle TimerHandle;
		float TimerSec = 3.0f;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				if (CurveFloat)
				{
					FVector Forward = GetActorForwardVector();

					FOnTimelineFloat TimelineProgress;
					FOnTimelineEvent LerpTimelineFinishedCallback;
					TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
					LerpTimelineFinishedCallback.BindUFunction(this, FName("TimelineFinished"));

					CurveFTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
					CurveFTimeline.SetTimelineFinishedFunc(LerpTimelineFinishedCallback);

					StartLoc = StartCameraComponent->GetComponentLocation();
					EndLoc = EndCameraComponent->GetComponentLocation();

					StartRot = StartCameraComponent->GetComponentRotation();
					EndRot = EndCameraComponent->GetComponentRotation();

					CurveFTimeline.SetTimelineLength(0.f);

					CurveFTimeline.PlayFromStart();
				}

				GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			}), TimerSec, false);
	}
}

// Called every frame
void ALightHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveFTimeline.TickTimeline(DeltaTime);
}

void ALightHouse::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (IsValid == false)
		{
			if (PressKeyWidgetClass)
			{
				PressKeyWidgetUIObejct = CreateWidget<UUserWidget>(GetWorld(), PressKeyWidgetClass);
				PressKeyWidgetUIObejct->AddToViewport();
			}
		}
	}
}

void ALightHouse::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (IsValid == false)
		{
			if (PressKeyWidgetUIObejct)
			{
				PressKeyWidgetUIObejct->RemoveFromParent();
			}
		}
	}
}

void ALightHouse::TimelineProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(StartLoc, EndLoc, Value);
	FRotator NewRotation = FMath::Lerp(StartRot, EndRot, Value);

	StartCameraComponent->SetWorldLocationAndRotation(NewLocation, NewRotation);
}

void ALightHouse::TimelineFinished()
{
	FTimerHandle TimerHandle;
	float TimerSec = 1.f;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{

			AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);

			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			PlayerController->SetViewTargetWithBlend(MyCharacter->CameraComponent->GetOwner(), 3.f);
			MyCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			PlayerController->SetInputMode(FInputModeGameOnly());
			MyCharacter->GetCharacterMovement()->Velocity = FVector(0.f, 0.f, 0.f);

			IsValid = true;

			PrimaryActorTick.bCanEverTick = false;
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), TimerSec, false);

}

