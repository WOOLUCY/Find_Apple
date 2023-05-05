// Fill out your copyright notice in the Description page of Project Settings.


#include "MainLevelScriptActor.h"
#include "Teleport/BlackScreenBegin.h"
#include "Teleport/BlackScreenEnd.h"
#include "FindAppleCharacter.h"
#include "Kismet/GameplayStatics.h"

AMainLevelScriptActor::AMainLevelScriptActor()
{

}

void AMainLevelScriptActor::BeginPlay()
{
	// ���� ������ �� õõ�� ������� ȿ���� ���� ���� ���� �ִϸ��̼� �߰�
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// ���콺�� ���߰� GameOn �� �ٲ�
	PlayerController->SetShowMouseCursor(false);
	PlayerController->SetInputMode(FInputModeGameOnly());
}
