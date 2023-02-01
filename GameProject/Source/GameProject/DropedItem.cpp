// Fill out your copyright notice in the Description page of Project Settings.


#include "DropedItem.h"
#include "Components/BoxComponent.h"
#include "InventoryDataTable.h"	
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ADropedItem::ADropedItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	MyBox->SetupAttachment(GetRootComponent());

	/* Box Static Mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (BoxMesh.Succeeded())
	{
		MyBox->SetStaticMesh(BoxMesh.Object);
		MyBox->SetRelativeLocationAndRotation(FVector(180.f, 0.f, 0.f), FRotator(0.f, 180.f, 0.f));
		MyBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MyBox->SetHiddenInGame(true);
	}

	/* Collision Mesh */
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 64.f), FRotator(0.f, 0.f, 0.f));
	CollisionMesh->SetBoxExtent(FVector(64.f, 64.f, 64.f));
	CollisionMesh->SetupAttachment(MyBox);

	//static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable'"));
	//if (DataTable.Succeeded())
	//{
	//	ItemDataTable = DataTable.Object;
	//}

}

// Called when the game starts or when spawned
void ADropedItem::BeginPlay()
{
	Super::BeginPlay();

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
				UE_LOG(LogTemp, Warning, TEXT("Apple "));
			}
		}
	}

	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &ADropedItem::OnOverlapEnd);
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ADropedItem::OnOverlapBegin);
}

// Called every frame
void ADropedItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADropedItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping!"));
	}
}

void ADropedItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

