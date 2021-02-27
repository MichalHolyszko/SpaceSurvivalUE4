// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBase.h"
#include "InventoryComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::Interact_Implementation(AActor* OtherActor)
{
	if(OtherActor != nullptr)
	{
		UInventoryComponent* Inventory = OtherActor->FindComponentByClass<UInventoryComponent>();
		if(Inventory != nullptr)
		{
			FSlot NewContent = FSlot();
			NewContent.ItemStruct = ItemStruct;
			NewContent.Quantity = 1;
			if(Inventory->AddToInventory(NewContent))
			{
				UE_LOG(LogTemp, Error, TEXT("XD"));
				Destroy();
			}
		}
	}
}

