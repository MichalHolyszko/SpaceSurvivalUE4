// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemContainer.h"
#include "DropComponent.h"

#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AItemContainer::AItemContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize Components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	Mesh->SetupAttachment(Root);

	DropComponent = CreateDefaultSubobject<UDropComponent>(TEXT("DropComponent"));

	// Initialize variables
	MaxHealth = 100.f;
	ActualHealth = MaxHealth;

	MaxQuantity = 1;
	ActualQuantity = MaxQuantity;
}

// Called when the game starts or when spawned
void AItemContainer::BeginPlay()
{
	Super::BeginPlay();
}

float AItemContainer::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(DropComponent != nullptr)
	{
		DropComponent->SetQuantity(ActualQuantity);
		DropComponent->DropItem();
	}

	return DamageAmount;
}

