// Fill out your copyright notice in the Description page of Project Settings.


#include "MainLevelScriptActor.h"
#include "Teleport/BlackScreenBegin.h"
#include "Teleport/BlackScreenEnd.h"
#include "Kismet/GameplayStatics.h"

AMainLevelScriptActor::AMainLevelScriptActor()
{
	//ConstructorHelpers::FClassFinder<UBlackScreenBegin>  UBlackScreenBeginWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_BlackScreenBegin.WBP_BlackScreenBegin_C'"));
	//if (UBlackScreenBeginWidget.Succeeded())
	//{
	//	BlackScreenBeginClass = UBlackScreenBeginWidget.Class;
	//}

	ConstructorHelpers::FClassFinder<UBlackScreenEnd>  UBlackScreenEndWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_BlackScreenEnd.WBP_BlackScreenEnd_C'"));
	if (UBlackScreenEndWidget.Succeeded())
	{
		BlackScreenEndClass = UBlackScreenEndWidget.Class;
	}
}

void AMainLevelScriptActor::BeginPlay()
{
	// 레벨 들어왔을 때 천천히 밝아지는 효과를 내기 위해 위젯 애니메이션 추가
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	BlackScreenEndUIObject = CreateWidget<UBlackScreenEnd>(GetWorld(), BlackScreenEndClass);
	BlackScreenEndUIObject->AddToViewport();

	// 마우스는 감추고 GameOn 로 바꿈
	PlayerController->SetShowMouseCursor(false);
	PlayerController->SetInputMode(FInputModeGameOnly());
}
