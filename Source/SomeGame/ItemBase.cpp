// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBase.h"
#include "InventoryComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Quantity = 1;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemBase::Interact_Implementation(AActor* OtherActor)
{
	if(OtherActor != nullptr)
	{
		AddToInventory(OtherActor, Quantity);
	}
}

void AItemBase::AddToInventory(AActor* InventoryOwner, int32 ItemQuantity)
{
	UInventoryComponent* Inventory = InventoryOwner->FindComponentByClass<UInventoryComponent>();
	if(Inventory != nullptr)
	{
		FSlot NewContent = FSlot();
		NewContent.ItemStruct = ItemStruct;
		NewContent.Quantity = ItemQuantity;

		if(Inventory->AddToInventory(NewContent))
		{
			Destroy();
		}
	}
}

