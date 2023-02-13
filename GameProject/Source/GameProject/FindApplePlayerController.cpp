// Fill out your copyright notice in the Description page of Project Settings.


#include "FindApplePlayerController.h"
#include "Blueprint/UserWidget.h"


AFindApplePlayerController::AFindApplePlayerController()
{
	//PlantWdiget = CreateDefaultSubobject<UPlantWidget>(TEXT("PlantWidget"));

	static ConstructorHelpers::FClassFinder<UPlantWidget> PLANT_WIDGET
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/kaon/UI/PlantOverlapWidget.PlantOverlapWidget_C'"));
	if (PLANT_WIDGET.Succeeded()) {
		PlantWidgetClass = PLANT_WIDGET.Class;
	}
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

	


}



void AFindApplePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}

void AFindApplePlayerController::ShowPlantWidget()
{


	PlantWdiget = CreateWidget<UPlantWidget>(this, PlantWidgetClass);
	PlantWdiget->AddToViewport();
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;


}
void AFindApplePlayerController::HiddenPlantWidget()
{

	PlantWdiget->RemoveFromParent();
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;



}