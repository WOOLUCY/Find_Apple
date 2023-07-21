// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStartWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "../Teleport/BlackScreenBegin.h"
#include "../Teleport/BlackScreenEnd.h"
#include "../MyGameInstance.h"

#include <string>


#include "GameOptionWidget.h"

UGameStartWidget::UGameStartWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
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

	ConstructorHelpers::FClassFinder<UGameOptionWidget>  OptionWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/GameStart/WBP_OptionWidget.WBP_OptionWidget_C'"));
	if (OptionWidget.Succeeded())
	{
		OptionWidgetClass = OptionWidget.Class;
	}
}

void UGameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &UGameStartWidget::GameStart);
	OptionButton->OnClicked.AddDynamic(this, &UGameStartWidget::CreateOptionWidget);
	IDTextBox->OnTextChanged.AddDynamic(this, &UGameStartWidget::ChangedIDTextBox);
}

void UGameStartWidget::GameStart()
{

	//여기가 스타트 버튼눌리는데 ID를 서버에 바로 보내지말고 
	//인스턴스에 저장해서 스타트누르면 소켓이랑 연결하는 방식으로 하는게 좋을듯

	auto MyInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyInstance != nullptr) {
		if (!MyInstance->MySocket.IsInit) {
			if (MyInstance->MySocket.InitSocket()) {
				MyInstance->MySocket.IsInit = true;

				char* result = TCHAR_TO_ANSI(*ID.ToString()); 

				if (MyInstance->MySocket.SendIngamePacket(result)) {
					UE_LOG(LogTemp, Warning, TEXT("SendIngamePacket() Success"));
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("SendIngamePacket() Fail"));

				}
			}
		}
	}


	BlackScreenPopStart();

	FTimerHandle TimerHandle;
	float BlackScreenBeginTime = 1.0;



	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			UGameplayStatics::OpenLevel(this, TransferLevelName);

			BlackScreenBeginUIObject->RemoveFromParent();

			BlackScreenPopEnd();

		}), BlackScreenBeginTime, false);

	RemoveFromParent();
} 

void UGameStartWidget::CreateOptionWidget()
{
	OptionUIObject = CreateWidget<UGameOptionWidget>(GetWorld(), OptionWidgetClass);
	OptionUIObject->AddToViewport();
}

void UGameStartWidget::BlackScreenPopStart()
{
	BlackScreenBeginUIObject = CreateWidget<UBlackScreenBegin>(GetWorld(), BlackScreenBeginClass);
	BlackScreenBeginUIObject->AddToViewport();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PlayerController->SetShowMouseCursor(false);
}

void UGameStartWidget::BlackScreenPopEnd()
{
	BlackScreenEndUIObject = CreateWidget<UBlackScreenEnd>(GetWorld(), BlackScreenEndClass);
	BlackScreenEndUIObject->AddToViewport();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(false);
}

void UGameStartWidget::ChangeLevelAndDestroy()
{
}

void UGameStartWidget::ChangedIDTextBox(const FText& Text)
{
	ID = Text;

	UE_LOG(LogTemp, Warning, TEXT("SomeString: %s"), *ID.ToString());
}
