// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMapWidget.h"
#include "Components/Button.h"
#include "BlackScreenBegin.h"
#include "BlackScreenEnd.h"
#include "LightHouse.h"
#include "../PlayerHouse.h"
#include "Kismet/GameplayStatics.h"
#include "../FindAppleCharacter.h"


UWorldMapWidget::UWorldMapWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	ConstructorHelpers::FClassFinder<UBlackScreenBegin>  UBlackScreenBeginWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_BlackScreenBegin.WBP_BlackScreenBegin_C'"));
	if (UBlackScreenBeginWidget.Succeeded())
	{
		BlackScreenBeginClass = UBlackScreenBeginWidget.Class;
	}
}

void UWorldMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// NPC 집에 대한 클릭, 호버, 비호버 처리
	TArray<AActor*> NPCHouses;
	//tag = FrontDungeon, NPCHouse, Bridge
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ALightHouse::StaticClass(), "NPCHouse", NPCHouses);

	for (AActor* Actor : NPCHouses)
	{
		ALightHouse* LightHouse = Cast<ALightHouse>(Actor);

		if (LightHouse != nullptr)
		{
			// 등록이 완료된 곳이라면 
			if ( true /*LightHouse->isPressed*/)
			{
				NPChouse->OnHovered.AddDynamic(this, &UWorldMapWidget::NPCHouseButtonHovered);
				NPChouse->OnUnhovered.AddDynamic(this, &UWorldMapWidget::NPCHouseButtonNotHovered);
				NPChouse->OnClicked.AddDynamic(this, &UWorldMapWidget::NPCHouseButtonClick);
			}
		}
	}

	// 다리 앞 등대에 대한 클릭, 호버, 비호버 처리
	TArray<AActor*> Bridges;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ALightHouse::StaticClass(), "Bridge", Bridges);

	for (AActor* Actor : Bridges)
	{
		ALightHouse* LightHouse = Cast<ALightHouse>(Actor);

		if (LightHouse != nullptr)
		{
			// 등록이 완료된 곳이라면 
			if (true /*LightHouse->isPressed*/)
			{
				Bridge->OnHovered.AddDynamic(this, &UWorldMapWidget::BridgeButtonHovered);
				Bridge->OnUnhovered.AddDynamic(this, &UWorldMapWidget::BridgeButtonNotHovered);
				Bridge->OnClicked.AddDynamic(this, &UWorldMapWidget::BridgeButtonClick);
			}
		}
	}
	
	// 던전 앞 등대에 대한 클릭, 호버, 비호버 처리
	TArray<AActor*> Dungeons;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ALightHouse::StaticClass(), "FrontDungeon", Dungeons);

	for (AActor* Actor : Dungeons)
	{
		ALightHouse* LightHouse = Cast<ALightHouse>(Actor);

		if (LightHouse != nullptr)
		{
			// 등록이 완료된 곳이라면 
			if (true /*LightHouse->isPressed*/)
			{
				FrontDungeon->OnHovered.AddDynamic(this, &UWorldMapWidget::FrontDungeonButtonHovered);
				FrontDungeon->OnUnhovered.AddDynamic(this, &UWorldMapWidget::FrontDungeonButtonNotHovered);
				FrontDungeon->OnClicked.AddDynamic(this, &UWorldMapWidget::FrontDungeonButtonClick);
			}
		}
	}

	/* Hover */
	Home->OnHovered.AddDynamic(this, &UWorldMapWidget::HomeButtonHovered);

	/* Not Hover */
	Home->OnUnhovered.AddDynamic(this, &UWorldMapWidget::HomeButtonNotHovered);

	/* Click (Teleport) */
	Home->OnClicked.AddDynamic(this, &UWorldMapWidget::HomeButtonClick);

	BlackScreenBeginUIObject = CreateWidget<UBlackScreenBegin>(GetWorld(), BlackScreenBeginClass);
	BlackScreenBeginUIObject->AddToViewport();
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
	float BlackScreenBeginTime = 1.5;

	/* 타이머 진행, 위젯이 흐려지는 동안은 이동하지 않도록 잠시 Delay 효과 */
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			/* (FName) 위치로 플레이어 이동 */
			TeleportPlayer("NPChouse");

			/* 점점 밝아지는 위젯 애니메이션 추가 */
			BlackScreenPopEnd();

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), BlackScreenBeginTime, false);


	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
	RemoveFromParent();
}

void UWorldMapWidget::FrontDungeonButtonClick()
{
	BlackScreenPopStart();
	FTimerHandle TimerHandle;
	float BlackScreenBeginTime = 1.5;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			TeleportPlayer("FrontDungeon");

			BlackScreenPopEnd();

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), BlackScreenBeginTime, false);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);

	RemoveFromParent();
}

void UWorldMapWidget::HomeButtonClick()
{
	BlackScreenPopStart();
	FTimerHandle TimerHandle;
	float BlackScreenBeginTime = 1.5;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			TeleportPlayer("Home");

			BlackScreenPopEnd();

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), BlackScreenBeginTime, false);


	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
	RemoveFromParent();
}

void UWorldMapWidget::BridgeButtonClick()
{
	BlackScreenPopStart();
	FTimerHandle TimerHandle;
	float BlackScreenBeginTime = 1.5;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			TeleportPlayer("Bridge");

			BlackScreenPopEnd();

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), BlackScreenBeginTime, false);


	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
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
				UE_LOG(LogTemp, Warning, TEXT("Home teleport"));
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
			}
		}
	}
	
}

void UWorldMapWidget::BlackScreenPopStart()
{
	BlackScreenBeginUIObject->BeginAnimation();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PlayerController->SetShowMouseCursor(false);
}

void UWorldMapWidget::BlackScreenPopEnd()
{
	BlackScreenBeginUIObject->EndAnimation();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(false);

	FTimerHandle TimerHandle;
	float BlackScreenEndTime = 0.8;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), BlackScreenEndTime, false);


}