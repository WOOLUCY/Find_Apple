// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMapWidget.h"
#include "Components/Button.h"
#include "BlackScreenBegin.h"
#include "BlackScreenEnd.h"
#include "TeleportNameWidget.h"
#include "LightHouse.h"
#include "../PlayerHouse.h"
#include "Kismet/GameplayStatics.h"
#include "../FindAppleCharacter.h"
#include "Components/TextBlock.h"


UWorldMapWidget::UWorldMapWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	ConstructorHelpers::FClassFinder<UBlackScreenBegin>  UBlackScreenBeginWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_BlackScreenBegin.WBP_BlackScreenBegin_C'"));
	if (UBlackScreenBeginWidget.Succeeded())
	{
		BlackScreenBeginClass = UBlackScreenBeginWidget.Class;
	}

	ConstructorHelpers::FClassFinder<UBlackScreenEnd>  UBlackScreenEndWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_BlackScreenEnd.WBP_BlackScreenEnd_C'"));
	if (UBlackScreenEndWidget.Succeeded())
	{
		BlackScreenEndClass = UBlackScreenEndWidget.Class;
	}

	ConstructorHelpers::FClassFinder<UTeleportNameWidget>  TeleportNameWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_TeleportName.WBP_TeleportName_C'"));
	if (TeleportNameWidget.Succeeded())
	{
		TeleportNameWidgetClass = TeleportNameWidget.Class;
	}
}

void UWorldMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/* Hover */
	NPChouse->OnHovered.AddDynamic(this, &UWorldMapWidget::NPCHouseButtonHovered);
	Home->OnHovered.AddDynamic(this, &UWorldMapWidget::HomeButtonHovered);
	FrontDungeon->OnHovered.AddDynamic(this, &UWorldMapWidget::FrontDungeonButtonHovered);
	Bridge->OnHovered.AddDynamic(this, &UWorldMapWidget::BridgeButtonHovered);

	/* Not Hover */
	NPChouse->OnUnhovered.AddDynamic(this, &UWorldMapWidget::NPCHouseButtonNotHovered);
	Home->OnUnhovered.AddDynamic(this, &UWorldMapWidget::HomeButtonNotHovered);
	FrontDungeon->OnUnhovered.AddDynamic(this, &UWorldMapWidget::FrontDungeonButtonNotHovered);
	Bridge->OnUnhovered.AddDynamic(this, &UWorldMapWidget::BridgeButtonNotHovered);

	/* Click (Teleport) */
	NPChouse->OnClicked.AddDynamic(this, &UWorldMapWidget::NPCHouseButtonClick);
	Home->OnClicked.AddDynamic(this, &UWorldMapWidget::HomeButtonClick);
	FrontDungeon->OnClicked.AddDynamic(this, &UWorldMapWidget::FrontDungeonButtonClick);
	Bridge->OnClicked.AddDynamic(this, &UWorldMapWidget::BridgeButtonClick);
}

void UWorldMapWidget::NPCHouseButtonHovered()
{
	NPChouse->SetRenderScale(FVector2D(2.f, 2.f));
}

void UWorldMapWidget::FrontDungeonButtonHovered()
{ 
	FrontDungeon->SetRenderScale(FVector2D(2.f, 2.f));
}

void UWorldMapWidget::HomeButtonHovered()
{
	Home->SetRenderScale(FVector2D(2.f, 2.f));
}

void UWorldMapWidget::BridgeButtonHovered()
{
	Bridge->SetRenderScale(FVector2D(2.f, 2.f));
}

void UWorldMapWidget::NPCHouseButtonNotHovered()
{
	NPChouse->SetRenderScale(FVector2D(1.f, 1.f));
}

void UWorldMapWidget::FrontDungeonButtonNotHovered()
{
	FrontDungeon->SetRenderScale(FVector2D(1.f, 1.f));
}

void UWorldMapWidget::HomeButtonNotHovered()
{
	Home->SetRenderScale(FVector2D(1.f, 1.f));
}

void UWorldMapWidget::BridgeButtonNotHovered()
{
	Bridge->SetRenderScale(FVector2D(1.f, 1.f));
}

void UWorldMapWidget::NPCHouseButtonClick()
{
	/* 어두워지는 위젯 애니메이션 추가 */
	BlackScreenPopStart();
	FTimerHandle TimerHandle;
	float BlackScreenBeginTime = 0.8;

	CurrentPlaceNum = 2;

	/* 타이머 진행, 위젯이 흐려지는 동안은 이동하지 않도록 잠시 Delay 효과 */
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			/* (FName) 위치로 플레이어 이동 */
			TeleportPlayer("NPChouse");

			BlackScreenBeginUIObject->RemoveFromParent();

			/* 점점 밝아지는 위젯 애니메이션 추가 */
			BlackScreenPopEnd();


			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), BlackScreenBeginTime, false);


	RemoveFromParent();
}

void UWorldMapWidget::FrontDungeonButtonClick()
{
	BlackScreenPopStart();
	FTimerHandle TimerHandle;
	float BlackScreenBeginTime = 0.8;

	CurrentPlaceNum = 4;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			TeleportPlayer("FrontDungeon");

			BlackScreenBeginUIObject->RemoveFromParent();

			BlackScreenPopEnd();

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), BlackScreenBeginTime, false);


	RemoveFromParent();
}

void UWorldMapWidget::HomeButtonClick()
{
	BlackScreenPopStart();
	FTimerHandle TimerHandle;
	float BlackScreenBeginTime = 0.8;

	CurrentPlaceNum = 1;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			TeleportPlayer("Home");

			BlackScreenBeginUIObject->RemoveFromParent();

			BlackScreenPopEnd();

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), BlackScreenBeginTime, false);


	RemoveFromParent();
}

void UWorldMapWidget::BridgeButtonClick()
{
	BlackScreenPopStart();
	FTimerHandle TimerHandle;
	float BlackScreenBeginTime = 0.8;

	CurrentPlaceNum = 3;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			TeleportPlayer("Bridge");

			BlackScreenBeginUIObject->RemoveFromParent();

			BlackScreenPopEnd();

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), BlackScreenBeginTime, false);


	RemoveFromParent();
}

void UWorldMapWidget::TeleportPlayer(FName Place)
{
	if (Place == "Home")
	{
		TArray<AActor*> HomeActor;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), APlayerHouse::StaticClass(), Place, HomeActor);
		for (AActor* Actor : HomeActor)
		{
			APlayerHouse* PlayerHome = Cast<APlayerHouse>(Actor);

			if (PlayerHome != nullptr)
			{
				FVector Location = PlayerHome->GetActorLocation();
				FVector Forward = PlayerHome->GetActorForwardVector() * FVector(1.f, 1.f, 1.f);
				FVector MoveLocation = Location + (Forward * 700.f) + FVector(0.f, 0.f, 50.f);

				AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				CharacterActor->SetActorRelativeLocation(MoveLocation);
			}
		}
	}
	else 
	{
		TArray<AActor*> LightHouses;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ALightHouse::StaticClass(), Place, LightHouses);

		for (AActor* Actor : LightHouses)
		{
			ALightHouse* LightHouse = Cast<ALightHouse>(Actor);

			if (LightHouse != nullptr)
			{
				FVector Location = LightHouse->GetActorLocation();
				FVector Forward = LightHouse->GetActorForwardVector() * FVector(1.f, 1.f, 1.f);
				FVector MoveLocation = Location + (Forward * 700.f) + FVector(0.f, 0.f, 50.f);

				AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				CharacterActor->SetActorRelativeLocation(MoveLocation);
				//UE_LOG(LogTemp, Warning, TEXT("Light house teleport, %s"), *Place.ToString());
			}
		}
	}
	
}

void UWorldMapWidget::BlackScreenPopStart()
{
	BlackScreenBeginUIObject = CreateWidget<UBlackScreenBegin>(GetWorld(), BlackScreenBeginClass);
	BlackScreenBeginUIObject->AddToViewport();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PlayerController->SetShowMouseCursor(false);
}

void UWorldMapWidget::BlackScreenPopEnd()
{
	BlackScreenEndUIObject = CreateWidget<UBlackScreenEnd>(GetWorld(), BlackScreenEndClass);
	BlackScreenEndUIObject->AddToViewport();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(false);


	FTimerHandle TimerHandle;
	float BlackScreenBeginTime = 1.f;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			BlackScreenEndUIObject->RemoveFromParent();

			DisplayNameWidget();
		}), BlackScreenBeginTime, false);
}

void UWorldMapWidget::DisplayNameWidget()
{
	TeleportNameWidgetUIObject = CreateWidget<UTeleportNameWidget>(GetWorld(), TeleportNameWidgetClass);

	FString PlaceName;
	if (CurrentPlaceNum == 1 ) { PlaceName = FString(TEXT("나의 집 앞")); }
	if (CurrentPlaceNum == 2) { PlaceName = FString(TEXT("파인 집 앞 등대")); }
	if (CurrentPlaceNum == 3) { PlaceName = FString(TEXT("다리 앞 등대")); }
	if (CurrentPlaceNum == 4) { PlaceName = FString(TEXT("던전 앞 등대")); }
	
	TeleportNameWidgetUIObject->PlaceText->SetText(FText::FromString(PlaceName));

	TeleportNameWidgetUIObject->AddToViewport();

	FTimerHandle TimerHandle;
	float AnimationTime = 5.5f;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			TeleportNameWidgetUIObject->RemoveFromParent();
		}), AnimationTime, false);
}
