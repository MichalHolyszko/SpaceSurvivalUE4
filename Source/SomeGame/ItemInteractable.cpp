// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemInteractable.h"

#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

AItemInteractable::AItemInteractable()
{
    PrimaryActorTick.bCanEverTick = false;

	// Initialize Components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	Mesh->SetupAttachment(Root);

    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(Root);
}

void AItemInteractable::Interact_Implementation(AActor* OtherActor)
{
	if(OtherActor != nullptr)
	{
		if(AddToInventory(OtherActor, Quantity))
		{
			SetActorEnableCollision(false);
			Destroy();
		}
	}
}

void AItemInteractable::ToggleOverlapping_Implementation()
{
    if(WidgetComponent != nullptr)
    {
        if(WidgetComponent->GetUserWidgetObject()->IsVisible())
		{
			WidgetComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			WidgetComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
		}
    }
}
