// Fill out your copyright notice in the Description page of Project Settings.


#include "LightHouse.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "ShowMapNameWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"
#include "../FindAppleCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TextBlock.h"
#include "AddMapWidget.h"
#include "../PressKeyWidget.h"

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
	PrimaryActorTick.bCanEverTick = true;

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

	/* Camera Components */
	FirstCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera1"));
	FirstCameraComponent->SetupAttachment(DefaultRoot);
	FirstCameraComponent->SetRelativeLocationAndRotation(FVector(2.665514, 493.564828, 669.388877), FRotator( -14.941587, -49.824560, -1.337803));

	SecondCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera2"));
	SecondCameraComponent->SetupAttachment(DefaultRoot);
	SecondCameraComponent->SetRelativeLocationAndRotation(FVector(2.665514, 173.564828, 669.388877), FRotator(-14.941587, 25.175439, -1.337803));

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionMesh->SetRelativeLocation(FVector(320.000000, 0.000000, 64.000000));
	CollisionMesh->SetBoxExtent(FVector(120.f, 120.f, 120.f));
	CollisionMesh->SetupAttachment(DefaultRoot);

	/* Show Name Widget */
	ConstructorHelpers::FClassFinder<UShowMapNameWidget>  MapNameWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_MapName.WBP_MapName_C'"));
	if (MapNameWidget.Succeeded())
	{
		MapNameWidgetClass = MapNameWidget.Class;
	}

	/* Press Key Widget */
	ConstructorHelpers::FClassFinder<UPressKeyWidget>  PressKeyWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_PressQ.WBP_PressQ_C'"));
	if (PressKeyWidget.Succeeded())
	{
		PressKeyClass = PressKeyWidget.Class;
	}

	// Timeline
	ConstructorHelpers::FObjectFinder<UCurveFloat>  CurveObject(TEXT("/Script/Engine.CurveFloat'/Game/Semin/UI/Map/CameraMove.CameraMove'"));
	if (CurveObject.Succeeded())
	{
		CurveFloat = CurveObject.Object;
	}

	// Add to Map Widget
	ConstructorHelpers::FClassFinder<UAddMapWidget>  AddMapWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_AddMap.WBP_AddMap_C'"));
	if (AddMapWidget.Succeeded())
	{
		AddToMapWidgetClass = AddMapWidget.Class;
	}
}

// Called when the game starts or when spawned
void ALightHouse::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &ALightHouse::OnOverlapEnd);
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ALightHouse::OnOverlapBegin);
}

// Called every frame
void ALightHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveFTimeline.TickTimeline(DeltaTime);
}

void ALightHouse::TimelineProgress(float Value)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FVector NewLocation = FMath::Lerp(StartLoc, EndLoc, Value);
	FRotator NewRotation = FMath::Lerp(StartRot, EndRot, Value);

	FirstCameraComponent->SetWorldLocation(NewLocation);
	FirstCameraComponent->SetWorldRotation(NewRotation);

	PlayerController->SetViewTarget(FirstCameraComponent->GetOwner());

	//PlayerController->GetCharacter()->GetCharacterMovement()->Velocity.X = 80.f;
}

void ALightHouse::TimelineFinished()
{
	MapNameWidgetUIObject->PlayAnimation(MapNameWidgetUIObject->MoveBorderHidden);

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			AActor* ActorItr = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(ActorItr);

			PlayerController->SetViewTargetWithBlend(MyCharacter->CameraComponent->GetOwner(), 3.f);
			MyCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			PlayerController->SetInputMode(FInputModeGameOnly());
			MyCharacter->GetCharacterMovement()->Velocity = FVector(0.f, 0.f, 0.f);
			//MapNameWidgetUIObject->RemoveFromParent();

			MapNameWidgetUIObject->RemoveFromParent();

			AddToMapWidgetUIObject = CreateWidget<UAddMapWidget>(GetWorld(), AddToMapWidgetClass);
			AddToMapWidgetUIObject->NameText->SetText(displayName);
			if (inves) 
			{
				AddToMapWidgetUIObject->Inves->SetText(FText::FromString(TEXT("이")));
			}
			AddToMapWidgetUIObject->AddToViewport();

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

		}), 1.f, false);
}

void ALightHouse::OnActivate_Implementation()
{
	if (isPressed == false) {

		isPressed = true;

		PressKeyUIObject->RemoveFromParent();

		MapNameWidgetUIObject = CreateWidget<UShowMapNameWidget>(GetWorld(), MapNameWidgetClass);

		if (this->ActorHasTag(FName(TEXT("Bridge"))))
		{
			FString placeName = TEXT("다리 앞 등대");
			displayName = FText::FromString(placeName);

			MapNameWidgetUIObject->NameText->SetText(displayName);
		}

		if (this->ActorHasTag(FName(TEXT("NPCHouse"))))
		{
			FString placeName = TEXT("레인의 집 옆");
			displayName = FText::FromString(placeName);
			inves = true;

			MapNameWidgetUIObject->NameText->SetText(displayName);
		}

		if (this->ActorHasTag(FName(TEXT("FrontDungeon"))))
		{
			FString placeName = TEXT("던전 앞 등대");
			displayName = FText::FromString(placeName);

			MapNameWidgetUIObject->NameText->SetText(displayName);
		}

		MapNameWidgetUIObject->AddToViewport();

		// Move camera 
		AActor* ActorItr = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(ActorItr);

		MyCharacter->GetCharacterMovement()->DisableMovement();
		MyCharacter->GetCharacterMovement()->Velocity = FVector(0.f, 0.f, 0.f);


		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->SetInputMode(FInputModeGameAndUI());

		PlayerController->SetViewTargetWithBlend(FirstCameraComponent->GetOwner(), 3.f);

		FTimerHandle TimerHandle;

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
					StartLoc = FirstCameraComponent->GetComponentLocation();
					EndLoc = SecondCameraComponent->GetComponentLocation();

					StartRot = FirstCameraComponent->GetComponentRotation();
					EndRot = SecondCameraComponent->GetComponentRotation();

					CurveFTimeline.SetTimelineLength(1.f);

					CurveFTimeline.PlayFromStart();
				}
				GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			}), 3.f, false);
		

		//MapNameWidgetUIObject->RemoveFromParent();

	}
}

void ALightHouse::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(OtherActor);

		if (MyCharacter) {
			if (isPressed)
			{
				MapNameWidgetUIObject = CreateWidget<UShowMapNameWidget>(GetWorld(), MapNameWidgetClass);
				MapNameWidgetUIObject->NameText->SetText(displayName);
				MapNameWidgetUIObject->AddToViewport();
				isKeyWidget = false;
			}
			else
			{
				PressKeyUIObject = CreateWidget<UPressKeyWidget>(GetWorld(), PressKeyClass);
				PressKeyUIObject->AddToViewport();
				isKeyWidget = true;
			}
			PrimaryActorTick.bCanEverTick = true;
		}
		
	}
}

void ALightHouse::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(OtherActor);
		PrimaryActorTick.bCanEverTick = false;

		if (MyCharacter) {
			if (isPressed && isKeyWidget == false) {
				MapNameWidgetUIObject->PlayAnimation(MapNameWidgetUIObject->MoveBorderHidden);

				FTimerHandle TimerHandle;

				GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
					{

						MapNameWidgetUIObject->RemoveFromParent();

						GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
					}), 1.f, false);
			}
			else if (isPressed == false && isKeyWidget == true)
			{
				PressKeyUIObject->RemoveFromParent();
			}
		}
	}
}

