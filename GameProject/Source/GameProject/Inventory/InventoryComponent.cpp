// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UInventoryComponent::AddToInventory(FName ItemName, int32 Quantity)
{
	int32 UpdateQuantity;
	if ( InventoryContent.Find(ItemName)) 
	{
		UpdateQuantity = *InventoryContent.Find(ItemName);
		UpdateQuantity += Quantity;
	}
	else 
	{
		UpdateQuantity = Quantity;
	}

	InventoryContent.Add(ItemName, UpdateQuantity);
}

bool UInventoryComponent::RemoveFromInventory(FName ItemName, int32 Quantity)
{
	int32 InventoryQuantity = *InventoryContent.Find(ItemName);
	if (Quantity <= InventoryQuantity)
	{
		if (InventoryQuantity - Quantity == 0)
		{
			InventoryContent.Remove(ItemName);
			return true;
		}

		else 
		{
			InventoryContent.Add(ItemName, InventoryQuantity - Quantity);
		}
	}
	else 
	{
		return false;
	}



	return false;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

