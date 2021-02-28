// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemContainer.h"
#include "ItemBase.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AItemContainer::AItemContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Quantity = 1;
	Health = 100;
}

// Called when the game starts or when spawned
void AItemContainer::BeginPlay()
{
	Super::BeginPlay();
	
}

