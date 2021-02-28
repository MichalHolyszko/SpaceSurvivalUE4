// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBase.h"
#include "InventoryComponent.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize Components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	Mesh->SetupAttachment(Root);

	// Initialize variables
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
		if(AddToInventory(OtherActor, Quantity))
		{
			Destroy();
		}
	}
}

bool AItemBase::AddToInventory(AActor* InventoryOwner, int32 ItemQuantity)
{
	UInventoryComponent* Inventory = InventoryOwner->FindComponentByClass<UInventoryComponent>();
	if(Inventory != nullptr)
	{
		FSlot NewContent = FSlot();
		NewContent.ItemStruct = ItemStruct;
		NewContent.Quantity = ItemQuantity;

		return Inventory->AddToInventory(NewContent);
	}
	else
	{
		return false;
	}
}

