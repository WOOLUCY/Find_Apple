// Fill out your copyright notice in the Description page of Project Settings.


#include "DropedItem.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "InventoryDataTable.h"	
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "InventoryComponent.h"
#include "../QuestNPC.h"
#include "../FindAppleCharacter.h"
#include "../PressKeyWidget.h"

// Sets default values
ADropedItem::ADropedItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	SetRootComponent(MyBox);
	//MyBox->SetupAttachment(GetRootComponent());

	/* Box Static Mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (BoxMesh.Succeeded())
	{
		MyBox->SetStaticMesh(BoxMesh.Object);
		MyBox->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(0.f, 180.f, 0.f));
		MyBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		MyBox->SetCollisionProfileName(TEXT("ItemCollision"));
		MyBox->SetSimulatePhysics(true);

	}

	/* Collision Mesh */
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionMesh->SetBoxExtent(FVector(30.f, 30.f, 30.f));
	CollisionMesh->SetupAttachment(MyBox);
	CollisionMesh->SetWorldLocation(MyBox->GetComponentLocation());
	CollisionMesh->SetHiddenInGame(false);

	/* Press key Widget */
	ConstructorHelpers::FClassFinder<UPressKeyWidget>  PressKeyWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Inventory/UI/BP/WBP_PressE.WBP_PressE_C'"));
	if (PressKeyWidget.Succeeded())
	{
		PressKeyWidgetClass = PressKeyWidget.Class;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;
	}

	bIsPressKeyValid = false;
	CollisionValid = false;
}

// Called when the game starts or when spawned
void ADropedItem::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->SetWorldLocation(MyBox->GetComponentLocation());

	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &ADropedItem::OnOverlapEnd);
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ADropedItem::OnOverlapBegin);

	if (ItemDataTable != nullptr)
	{
		ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
		TArray<FName> RowNames = ItemDataTable->GetRowNames();

		for (FName RowName : RowNames)
		{
			FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

			if (RowName == ItemName)
			{
				MyBox->SetStaticMesh(InventoryRow.Mesh3D);
				MyBox->SetWorldScale3D(InventoryRow.MeshScale);
				MyBox->SetMaterial(0, InventoryRow.Mesh3D->GetMaterial(0));
			}
		}
	}
	bIsPressKeyValid = false;
	CollisionValid = false;

	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ADropedItem::CollisionStart, 1.0f, false);
}

// Called every frame
void ADropedItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CollisionMesh->SetWorldLocation(MyBox->GetComponentLocation());

}

void ADropedItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (CollisionValid) 
		{
			AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(OtherActor);

			if (MyCharacter) {
				if (bIsPressKeyValid == false)
				{
					MyCharacter->PressE = true;
					MyCharacter->LookAtActorPressE = this;
					bIsPressKeyValid = true;
					PressKeyWidgetUIObejct = CreateWidget<UPressKeyWidget>(GetWorld(), PressKeyWidgetClass);
					PressKeyWidgetUIObejct->AddToViewport();
					// UE_LOG(LogTemp, Warning, TEXT("Item Name: %s"), *ItemName.ToString());
				}
			}
		}
	}
}

void ADropedItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (CollisionValid)
		{
			AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(OtherActor);

			if (MyCharacter) {
				if (bIsPressKeyValid == true)
				{
					MyCharacter->PressE = false;
					PressKeyWidgetUIObejct->RemoveFromParent();
					bIsPressKeyValid = false;
				}
			}
		}
	}
}

void ADropedItem::ItemFresh(FName ItemReName)
{
	if (ItemDataTable != nullptr)
	{
		ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
		TArray<FName> RowNames = ItemDataTable->GetRowNames();
		ItemName = ItemReName;

		for (FName RowName : RowNames)
		{
			FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

			if (RowName == ItemReName)
			{
				MyBox->SetStaticMesh(InventoryRow.Mesh3D);
				MyBox->SetWorldScale3D(InventoryRow.MeshScale);
				MyBox->SetMaterial(0, InventoryRow.Mesh3D->GetMaterial(0));
			}
		}
	}
}

void ADropedItem::PicUpItem_Implementation()
{
	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(CharacterActor);
	MyCharacter->InventoryComponent->AddToInventory(ItemName, 1);

	TArray<AQuestNPC*> MyActors;
	TArray<AActor*> OutActors;

	/* 배치된 NPC 캐릭터 찾기 */
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AQuestNPC::StaticClass(), OutActors);
	for (AActor* a : OutActors)
	{
		MyActors.Add(Cast<AQuestNPC>(a));
	}

	for (AQuestNPC* FoundActor : MyActors)
	{
		if (FoundActor->QuestRequirItem.Find(ItemName))
		{
			if (*FoundActor->QuestRequirItem.Find(ItemName) == *MyCharacter->InventoryComponent->InventoryContent.Find(ItemName))
			{
				//
				//->AddOnScreenDebugMessage(-1, 4, FColor::Blue, TEXT("I Finished Quest !!"));
				FoundActor->Text->SetText(FText::FromString(TEXT("?")));
				FoundActor->Conversation_ID += 1;
				//UE_LOG(LogTemp, Warning, TEXT("%d Conversation ID "), FoundActor->Conversation_ID);
				FoundActor->CurrentLine = 0;
			}
		}

	}

	Destroy();
}

void ADropedItem::CollisionStart()
{
	CollisionMesh->SetWorldLocation(MyBox->GetComponentLocation());
	CollisionValid = true;

}
