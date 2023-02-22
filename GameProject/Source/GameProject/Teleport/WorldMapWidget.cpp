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

	ConstructorHelpers::FClassFinder<UBlackScreenEnd>  UBlackScreenEndWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_BlackScreenEnd.WBP_BlackScreenEnd_C'"));
	if (UBlackScreenEndWidget.Succeeded())
	{
		BlackScreenEndClass = UBlackScreenEndWidget.Class;
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
	/* ��ο����� ���� �ִϸ��̼� �߰� */
	BlackScreenPopStart();
	FTimerHandle TimerHandle;
	float BlackScreenBeginTime = 0.8;

	/* Ÿ�̸� ����, ������ ������� ������ �̵����� �ʵ��� ��� Delay ȿ�� */
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			/* (FName) ��ġ�� �÷��̾� �̵� */
			TeleportPlayer("NPChouse");

			BlackScreenBeginUIObject->RemoveFromParent();

			/* ���� ������� ���� �ִϸ��̼� �߰� */
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
	UE_LOG(LogTemp, Warning, TEXT("TeleportPlayer"));
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
				FVector MoveLocation = Location + (Forward * 700.f);

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
				FVector MoveLocation = Location + (Forward * 300.f);

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
}