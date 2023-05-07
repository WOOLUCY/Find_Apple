// Fill out your copyright notice in the Description page of Project Settings.


#include "FindApplePlayerController.h"
#include "Kismet/GameplayStatics.h"


#include "Blueprint/UserWidget.h"


AFindApplePlayerController::AFindApplePlayerController()
{
	IsTick = false;
}

void AFindApplePlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AFindApplePlayerController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

}

void AFindApplePlayerController::BeginPlay()
{

	MyInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyInstance != nullptr) {
		if (!MyInstance->MySocket.IsInit) {
			if (MyInstance->MySocket.InitSocket()) {
				MyInstance->MySocket.IsInit = true;
				if (MyInstance->MySocket.SendIngamePacket()) {
					IsTick = true;
				}
			}
		}
	}

}



void AFindApplePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}
void AFindApplePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (IsTick) {
		MyInstance->MySocket.PacketRecv();
	}
}
