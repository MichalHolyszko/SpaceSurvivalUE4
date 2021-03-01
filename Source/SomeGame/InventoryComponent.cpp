// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

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
	UE_LOG(LogTemp, Warning, TEXT("Inventory Slots: %i"), Inventory.Num());
}

bool UInventoryComponent::AddToInventory(const FSlot &ContentToAdd)
{
	if(ContentToAdd.ItemStruct.bIsStackable)
	{
		// Look in Inventory for Item with same Class. If found, add quantities, else try to create new stack
		return AddStackable(ContentToAdd);
	}
	else
	{
		// If item is not stackable, look for empty Slot in which Item can be added
		return CreateStack(ContentToAdd);
	}
}

bool UInventoryComponent::AddStackable(const FSlot &ContentToAdd)
{
	for(FSlot &Slot : Inventory)
	{
		if(Slot.ItemStruct.Class == ContentToAdd.ItemStruct.Class)
		{
			Slot.ItemStruct = ContentToAdd.ItemStruct;
			Slot.Quantity += ContentToAdd.Quantity;
			return true;
		}
	}

	return CreateStack(ContentToAdd);
}

bool UInventoryComponent::CreateStack(const FSlot &ContentToAdd)
{
	FSlot EmptySlot = FSlot();
	int32 EmptySlotIndex;

	if(Inventory.Find(EmptySlot, EmptySlotIndex))
	{
		Inventory[EmptySlotIndex] = ContentToAdd;

		UE_LOG(LogTemp, Warning, TEXT("Empty Slot Index: %i"), EmptySlotIndex);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Empty Slot NOT FOUND!: %i"));
		return false;
	}
}

/*  If Item is Consumable & Stackable, decrement Quantity, if Quantity == 0 make empty slot in that index
	If Item is Consumable & not Stackable make empty slot in that index
	If Item is not Consumable slot stay the same
*/
void UInventoryComponent::RefreshInventorySlot(int32 Index)
{	
	FSlot* UsedSlot = &Inventory[Index];
	
	if(UsedSlot->ItemStruct.bIsConsumable)
	{
		if(UsedSlot->ItemStruct.bIsStackable)
		{
			UsedSlot->Quantity--;
			if(UsedSlot->Quantity <= 0)
			{
				Inventory[Index] = FSlot();
			}
		}
		else
		{
			Inventory[Index] = FSlot();
		}
	}
}

// Check if quantity of Item is in Inventory 
bool UInventoryComponent::InventoryQuery(TSubclassOf<AItemBase> ItemClass, int32 QueryAmmount)
{
	int32 ItemQuantity = 0;

	for(FSlot Slot : Inventory)
	{
		if(Slot.ItemStruct.Class == ItemClass)
		{
			ItemQuantity += Slot.Quantity;
		}
	}

	return ItemQuantity >= QueryAmmount;
}




