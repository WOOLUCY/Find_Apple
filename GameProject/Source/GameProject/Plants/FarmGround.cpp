// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmGround.h"
#include "Kismet/GameplayStatics.h"

#include "../FindAppleGameMode.h"
#include "../FindApplePlayerController.h"
#include "../FindAppleCharacter.h"

#include "Plant.h"
#include "Tomato.h"
#include "RootPlant.h"


// Sets default values
AFarmGround::AFarmGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	CheckMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckMesh"));
	

	Overlap = CreateDefaultSubobject<UMaterial>(TEXT("BLUE"));
	NotWet = CreateDefaultSubobject<UMaterial>(TEXT("NotWet"));
	Wet = CreateDefaultSubobject<UMaterial>(TEXT("Wet"));


	RootComponent = Mesh;
	Mesh->SetRelativeRotation(FRotator(0, 90.f, 0));
	Box->SetupAttachment(RootComponent);
	

	Mesh->SetRelativeScale3D(FVector(1.5f, 1.5 , 1.f));

	Box->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	CheckMesh->SetupAttachment(Mesh);

	Mesh->SetCollisionProfileName("NoCollision");
	Box->SetCollisionProfileName("OverlapAll");


	IsEmpty = true;
	CanPutSeed = false;
	IsWet = false;
	Planted = nullptr;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/MouseOverlap.MouseOverlap'"));
	if (SM_MESH.Succeeded()){
		Mesh->SetStaticMesh(SM_MESH.Object);
		CheckMesh->SetStaticMesh(SM_MESH.Object);
		CheckMesh->SetRelativeLocation(FVector(0, 0, 1));
	}

	//위젯
	static ConstructorHelpers::FClassFinder<UPlantWidget> PLANT_WIDGET
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/kaon/UI/PlantOverlapWidget.PlantOverlapWidget_C'"));
	if (PLANT_WIDGET.Succeeded()) {
		PlantWidgetClass = PLANT_WIDGET.Class;
	}




	//머터리얼불러오기
	static ConstructorHelpers::FObjectFinder<UMaterial>Mat_Blue
	(TEXT("/Script/Engine.Material'/Game/kaon/asset/material/M_GroundBlue.M_GroundBlue'"));
	if (Mat_Blue.Succeeded()) {
		CheckMesh->SetMaterial(0, Mat_Blue.Object);
		CheckMesh->SetVisibility(false);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>Mat_Wet
	(TEXT("/Script/Engine.Material'/Game/kaon/asset/material/M_Wet.M_Wet'"));
	if (Mat_Wet.Succeeded()) {
		Wet = Mat_Wet.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>Mat_NotWet
	(TEXT("/Script/Engine.Material'/Game/kaon/asset/material/M_NotWet.M_NotWet'"));
	if (Mat_NotWet.Succeeded()) {
		NotWet = Mat_NotWet.Object;
	}


	Mesh->SetVisibility(true);

	Box->OnComponentBeginOverlap.AddDynamic(this, &AFarmGround::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &AFarmGround::OnOverlapEnd);




}
void AFarmGround::PostInitializeComponents()
{
	Super::PostInitializeComponents();



}


// Called when the game starts or when spawned
void AFarmGround::BeginPlay()
{
	Super::BeginPlay();
	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr) {

		auto hero = UGameplayStatics::GetPlayerCharacter(TheWorld, 0);
		Anim = Cast<UFindAppleAnimInstance>(hero->GetMesh()->GetAnimInstance());

		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		AFindAppleGameMode* MyMode = Cast<AFindAppleGameMode>(GameMode);

		if (MyMode != nullptr) {
			MyDelegateHandle = MyMode->DayChangeDelegate.AddUObject(
				this, &AFarmGround::DayChange);
		}


	}

}




// Called every frame
void AFarmGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFarmGround::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	auto hero = Cast<AFindAppleCharacter>(OtherActor);
	if (hero != nullptr) {
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("Overlap with Character"));
		CheckMesh->SetVisibility(true);

		ShowPlantWidget();
	}
	else {
		return;
	}

}

void AFarmGround::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto hero = Cast<AFindAppleCharacter>(OtherActor);
	if (hero != nullptr) {
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Overlap end with Character"));
		CheckMesh->SetVisibility(false);
		HiddenPlantWidget();

	}
	else {
		return;
	}


}

void AFarmGround::PutWater()
{
	UE_LOG(LogTemp, Warning, TEXT("WHY??"));
	if (IsWet ) {
		return;
	}
	else if(!IsWet && !IsEmpty) {
		cloud = GetWorld()->SpawnActor<ACloud>(GetActorLocation(), GetActorRotation());
		Mesh->SetMaterial(0, Wet);
		IsWet = true;
		cloud = nullptr;
		Planted->PutWater();
	}
	

	
}

void AFarmGround::PutSeed()
{

	if (IsEmpty==false) {
		//이미 점유되어있음 - 안내문띄우기

		return;
	}
	else {

		Anim->PlayPlantMontage();
		IsEmpty = false;

		UWorld* TheWorld = GetWorld();
		if (TheWorld) {
			//여기서 랜덤으로 나타나게 변경해야한다.
			Planted = TheWorld->SpawnActor<APlant>(ATomato::StaticClass(), GetActorLocation(), FRotator());
				
		}

	}
}

void AFarmGround::Harvest()
{
	Planted->Harvest();
}


void AFarmGround::ShowPlantWidget()
{
	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr) {

		auto hero = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AFindApplePlayerController* MyContorller = Cast<AFindApplePlayerController>(hero);
		if (MyContorller != nullptr) {
			PlantWdiget = CreateWidget<UPlantWidget>(MyContorller, PlantWidgetClass);
			PlantWdiget->AddToViewport();
			MyContorller->SetInputMode(FInputModeGameAndUI());
			MyContorller->bShowMouseCursor = true;

			PlantWdiget->SeedDelegate.BindUObject(this, &AFarmGround::PutSeed);
			PlantWdiget->WaterDelegate.BindUObject(this, &AFarmGround::PutWater);
			PlantWdiget->HarvestDelegate.BindUObject(this, &AFarmGround::Harvest);

		}



	}



}
void AFarmGround::HiddenPlantWidget()
{

	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr) {

		auto hero = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AFindApplePlayerController* MyContorller = Cast<AFindApplePlayerController>(hero);
		if (MyContorller != nullptr) {
			PlantWdiget->RemoveFromParent();
			MyContorller->SetInputMode(FInputModeGameOnly());
			MyContorller->bShowMouseCursor = false;

			PlantWdiget->SeedDelegate.Unbind();
			PlantWdiget->WaterDelegate.Unbind();
			PlantWdiget->HarvestDelegate.Unbind();

		}
	}

}

void AFarmGround::DayChange()
{
	UE_LOG(LogTemp, Warning, TEXT("FarmDaychange"));

	if (IsWet) {
	Mesh->SetMaterial(0, NotWet);
	IsWet = false;
	}
	else {
		if (Planted != nullptr) {
			Planted->DayChange();
		}
	}
		//else {
	//Planted->DayChange();

	//}

}
