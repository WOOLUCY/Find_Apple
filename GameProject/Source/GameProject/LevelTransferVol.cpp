// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransferVol.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "KaonWidget/DoorWidget.h"


#include "FindAppleGameMode.h"
#include "FindApplePlayerController.h"
#include "FindAppleCharacter.h"
#include "Dialogue/TeleportPosition.h"

#include "Teleport/BlackScreenBegin.h"


// Sets default values
ALevelTransferVol::ALevelTransferVol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TransferVol = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVol;
	
	TransferVol->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));


	//위젯
	static ConstructorHelpers::FClassFinder<UDoorWidget> DOOR_WIDGET
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/kaon/UI/DoorOverlap.DoorOverlap_C'"));

	if (DOOR_WIDGET.Succeeded()) {
		DoorWidgetClass = DOOR_WIDGET.Class;
	}
}

void ALevelTransferVol::NotifyActorBeginOverlap(AActor* OtherActor)
{

	//오버랩된게 캐릭터일때 위젯띄우는거로 하면될듯
	auto hero = Cast<AFindAppleCharacter>(OtherActor);


	if (hero != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("OverlapBegin Comple pereofjdskfjksdlfjsdklfjsdklfj"));
		ShowWdiget();
	}
	else {
		return;
	}

}

void ALevelTransferVol::NotifyActorEndOverlap(AActor* OtherActor)
{
	HiddenWidget();
}

// Called when the game starts or when spawned
void ALevelTransferVol::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelTransferVol::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ALevelTransferVol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelTransferVol::ShowWdiget()
{
	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr) {

		auto hero = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AFindApplePlayerController* MyContorller = Cast<AFindApplePlayerController>(hero);
		if (MyContorller != nullptr) {

			UE_LOG(LogTemp, Warning, TEXT("ShowWidet"));
			if (IsVisibleWidget == false) 
			{
				DoorWdiget = CreateWidget<UDoorWidget>(MyContorller, DoorWidgetClass);
				DoorWdiget->AddToViewport();

			}
			MyContorller->SetInputMode(FInputModeGameAndUI());
			MyContorller->bShowMouseCursor = true;



			DoorWdiget->YesDelegate.BindUObject(this, &ALevelTransferVol::YesChoice);
			DoorWdiget->NoDelegate.BindUObject(this, &ALevelTransferVol::NoChoice);


			IsVisibleWidget = true;
		}
	}




}
void ALevelTransferVol::HiddenWidget()
{

	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr) {

		auto hero = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AFindApplePlayerController* MyContorller = Cast<AFindApplePlayerController>(hero);
		if (MyContorller != nullptr) {
			if (IsVisibleWidget == true) {
				DoorWdiget->RemoveFromParent();
			}
			MyContorller->SetInputMode(FInputModeGameOnly());
			MyContorller->bShowMouseCursor = false;

			DoorWdiget->YesDelegate.Unbind();
			DoorWdiget->NoDelegate.Unbind();

			IsVisibleWidget = false;
		}
	}

}

void ALevelTransferVol::YesChoice()
{
	UE_LOG(LogTemp, Warning, TEXT("void ALevelTransferVol::YesChoice"));

	auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (TransferLevelName == FString("NPC"))
	{
		TeleportPointName = FName("NPCHousePoint");
		MovePointAtTeleport();
		return;
	}

	else if (TransferLevelName == FString("NPCHouseOut"))
	{
		TeleportPointName = FName("RainHouse");
		MovePointAtTeleport();
		return;
	}

	else if (TransferLevelName == FString("HEROHousePoint"))
	{
		TeleportPointName = FName("HEROHousePoint");
		MovePointAtTeleport();
		return;
	}

	else if (TransferLevelName == FString("HEROHouseOut"))
	{
		TeleportPointName = FName("HEROHouseOut");
		MovePointAtTeleport();
		return;
	}

	else if (TransferLevelName == FString("FightMap"))
	{
		TeleportPointName = FName("FightMapIn");
		MovePointAtTeleport();
		return;
	}

	else if (TransferLevelName == FString("FightMapOut"))
	{
		TeleportPointName = FName("FightMapOut");
		MovePointAtTeleport();
		return;
	}

	else if (TransferLevelName == FString("DungeonMapIn"))
	{
		TeleportPointName = FName("DungeonPoint");
		MovePointAtTeleport();
		return;
	}

	else if (TransferLevelName == FString("DungeonMapOut"))
	{
		TeleportPointName = FName("DungeonMapOut");
		MovePointAtTeleport();
		return;
	}

	else if (TransferLevelName == FString("CaveIn"))
	{
		TeleportPointName = FName("CaveIn");
		MovePointAtTeleport();
		return;
	}

	else if (TransferLevelName == FString("CaveOut"))
	{
		TeleportPointName = FName("CaveOut");
		MovePointAtTeleport();
		return;
	}


	else {
		if (GameInstance != nullptr) {
			FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
			FString Name = "EditMap";
			if (LevelName.Equals(Name)) {

				UE_LOG(LogTemp, Warning, TEXT("LevelTransfer cpp eqaul"));
				FVector temp = TransferVol->GetRelativeLocation();
				FVector ForwardVector = TransferVol->GetForwardVector();
				FVector MoveDirection = ForwardVector * 200;
				FVector NewLocation = temp + MoveDirection;
				UE_LOG(LogTemp, Warning, TEXT("%d %d %d"), NewLocation.X, NewLocation.Y, NewLocation.Z);

				GameInstance->SetCharLoc(NewLocation);

			}

		}
		UGameplayStatics::OpenLevel(this, *TransferLevelName);
	}



}

void ALevelTransferVol::NoChoice()
{
	UE_LOG(LogTemp, Warning, TEXT("void ALevelTransferVol::NoChoice"));
	HiddenWidget();

}

void ALevelTransferVol::MovePointAtTeleport()
{
	TArray<AActor*> TeleportActors;



	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATeleportPosition::StaticClass(), TeleportPointName, TeleportActors);

	{
		for (AActor* Actor : TeleportActors)
		{
			ATeleportPosition* Position = Cast<ATeleportPosition>(Actor);

			if (Position != nullptr)
			{
				FTimerHandle TimerHandle;
				float BlackScreenBeginTime = 0.8;

				AActor* ActorItr = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(ActorItr);

				FVector Location = Position->GetActorLocation();
				FVector MoveLocation = Location + FVector(0.f, 0.f, 50.f);

				FRotator MoveRotate = Position->GetActorRotation();

				MyCharacter->MoveLocation = MoveLocation;
				MyCharacter->MoveRotation = MoveRotate;
				MyCharacter->BlackScreenPopStart();

				HiddenWidget();
				//GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
				//	{
				//		//MyCharacter->SetActorRelativeLocation(MoveLocation);

				//		//BlackScreenEndAnim();

				//		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
				//	}), BlackScreenBeginTime, false);

			}
		}
	}
}


void ALevelTransferVol::BlackScreenEndAnim()
{
	AActor* ActorItr = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(ActorItr);
	MyCharacter->BlackScreenPopEnd();
}