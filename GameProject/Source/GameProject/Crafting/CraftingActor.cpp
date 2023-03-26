// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingActor.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "CraftingAllWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../PressKeyWidget.h"


// Sets default values
ACraftingActor::ACraftingActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Set Mesh */
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObject
	(TEXT("/Script/Engine.StaticMesh'/Game/kaon/asset/model/NPC_Bench.NPC_Bench'"));
	if (MeshObject.Succeeded()) {
		StaticMesh->SetStaticMesh(MeshObject.Object);
		StaticMesh->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	}

	/* Set Collision Box */
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionMesh->SetRelativeLocationAndRotation(FVector(110.f, -10.f, 0.f), FRotator(0.f, 0.f, 0.f));
	CollisionMesh->SetBoxExtent(FVector(140.f, 140.f, 140.f));
	CollisionMesh->SetupAttachment(StaticMesh);

	/* Press key Widget */
	ConstructorHelpers::FClassFinder<UUserWidget>  PressKeyWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Crafting/UI/WBP_PressQtoCrafting.WBP_PressQtoCrafting_C'"));
	if (PressKeyWidget.Succeeded())
	{
		PressKeyWidgetClass = PressKeyWidget.Class;
	}

	/* Crafting All Widget */
	ConstructorHelpers::FClassFinder<UCraftingAllWidget>  CraftingAllWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Crafting/UI/WBP_CraftingAll.WBP_CraftingAll_C'"));
	if (CraftingAllWidget.Succeeded())
	{
		CraftingAllWidgetClass = CraftingAllWidget.Class;
	}
}

// Called when the game starts or when spawned
void ACraftingActor::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &ACraftingActor::OnOverlapEnd);
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ACraftingActor::OnOverlapBegin);
}

// Called every frame
void ACraftingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACraftingActor::OnActivate_Implementation()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Overlap & Press Q"));
	if (bIsWidgetValid)	/* Already Widget is created */
	{
		//bIsWidgetValid = false;
		//CraftingAllUIObject->RemoveFromParent();
		//PlayerController->SetInputMode(FInputModeGameOnly());
		//PlayerController->SetShowMouseCursor(false);
	}
	else
	{
		bIsWidgetValid = true;
		CraftingAllUIObject = CreateWidget<UCraftingAllWidget>(GetWorld(), CraftingAllWidgetClass);
		CraftingAllUIObject->AddToViewport();
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
	}
}


void ACraftingActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (bIsPressKeyValid == false)
		{
			bIsPressKeyValid = true;
			PressKeyWidgetUIObejct = CreateWidget<UUserWidget>(GetWorld(), PressKeyWidgetClass);
			PressKeyWidgetUIObejct->AddToViewport();
		}

	}
}

void ACraftingActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Overlap End"));
		if (bIsPressKeyValid == true)
		{
			PressKeyWidgetUIObejct->RemoveFromParent();
			bIsPressKeyValid = false;
		}
		//if (bIsWidgetValid) {
		//	DialogueUIObject->RemoveFromParent();
		//	bIsWidgetValid = false;
		//	CurrentLine = 0;
		//}
	}
}
