// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	PrepareInventory();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInventoryComponent::ToggleInventory()
{
	OnToggleInventory.Broadcast();
}

void UInventoryComponent::PrepareInventory()
{
	Inventory.SetNum(NumberOfSlots);
}

bool UInventoryComponent::AddToInventory(const FSlot &ContentToAdd)
{
	if(!ContentToAdd.ItemStruct.bIsStackable)
	{
		CreateStack(ContentToAdd);
	}


	return true;
}

void UInventoryComponent::CreateStack(const FSlot &ContentToAdd)
{
	FSlot EmptySlot = FSlot();
	int32 EmptySlotIndex;

	if(Inventory.Find(EmptySlot, EmptySlotIndex))
	{
		Inventory[EmptySlotIndex] = ContentToAdd;
	}

	UE_LOG(LogTemp, Warning, TEXT("Empty Slot Index: %i"), EmptySlotIndex);
}




