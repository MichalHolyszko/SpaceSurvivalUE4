// Fill out your copyright notice in the Description page of Project Settings.

#include "DropComponent.h"
#include "ItemBase.h"

#include "Kismet/GameplayStatics.h"

UDropComponent::UDropComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Quantity = 1;
}

void UDropComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UDropComponent::DropItem()
{
	if(ItemClass != nullptr)
	{
		Item = GetWorld()->SpawnActor<AItemBase>(ItemClass);

		if(Item != nullptr)
		{
			APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
			if(PlayerPawn != nullptr)
			{
				Item->AddToInventory(PlayerPawn, Quantity);
			}
		}
	}
}
