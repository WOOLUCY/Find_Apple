// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"

#include "FindAppleCharacter.h"
#include "FindApplePlayerController.h"
#include "AuctionSemin/AuctionEnterWidget.h"
#include "Plants/FarmGround.h"

// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));

	RootComponent = Mesh;
	Mesh->SetRelativeRotation(FRotator(0, 90.f, 0));
	Box->SetupAttachment(RootComponent);

	Mesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	Box->SetRelativeScale3D(FVector(5.f, 5.f, 8.f));

	Mesh->SetCollisionProfileName("BlockAll");
	Box->SetCollisionProfileName("OverlapAll");

	// Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH
	(TEXT("/Script/Engine.StaticMesh'/Game/Semin/Asset/Spaceship/SM_Spaceship.SM_Spaceship'"));
	if (SM_MESH.Succeeded()) {
		Mesh->SetStaticMesh(SM_MESH.Object);
	}

	// Widget
	static ConstructorHelpers::FClassFinder<UTradeWidget> TRADE_WIDGET
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Woo/UI/TradeWidget.TradeWidget_C'"));
	if (TRADE_WIDGET.Succeeded()) {
		TradeWidgetClass = TRADE_WIDGET.Class;
	}

	// Semin
	ConstructorHelpers::FClassFinder<UAuctionEnterWidget> AuctionEnterWidgetFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Auction/WBP_AuctionAll.WBP_AuctionAll_C'"));
	if (AuctionEnterWidgetFinder.Succeeded())
	{
		AuctionWidgetClass = AuctionEnterWidgetFinder.Class;
	}

	Mesh->SetVisibility(true);

	Box->OnComponentBeginOverlap.AddDynamic(this, &ASpaceShip::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &ASpaceShip::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpaceShip::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASpaceShip::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto hero = Cast<AFindAppleCharacter>(OtherActor);
	if (hero != nullptr) {
		ShowTradeWidget();
	}
	else {
		return;
	}
}

void ASpaceShip::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto hero = Cast<AFindAppleCharacter>(OtherActor);
	if (hero != nullptr) {
		HideTradeWidget();
	}
	else {
		return;
	}
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpaceShip::ShowTradeWidget()
{
	auto hero = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFindApplePlayerController* MyContorller = Cast<AFindApplePlayerController>(hero);

	TradeWidget = CreateWidget<UTradeWidget>(GetWorld(), TradeWidgetClass);
	//AuctionWidgetUIObject = CreateWidget<UAuctionEnterWidget>(GetWorld(), AuctionWidgetClass);
	//TradeWidget->AuctionWidgetUIObject = AuctionWidgetUIObject;
	//AuctionWidgetUIObject->SetVisibility()
	TradeWidget->AddToViewport();

	MyContorller->SetInputMode(FInputModeGameAndUI());
	MyContorller->bShowMouseCursor = true;
}

void ASpaceShip::HideTradeWidget()
{
	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr) {

		auto hero = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AFindApplePlayerController* MyContorller = Cast<AFindApplePlayerController>(hero);
		if (MyContorller != nullptr) {
			TradeWidget->AuctionWidgetUIObject->RemoveFromParent();
			TradeWidget->RemoveFromParent();
			MyContorller->SetInputMode(FInputModeGameOnly());
			MyContorller->bShowMouseCursor = false;
		}
	}
}
