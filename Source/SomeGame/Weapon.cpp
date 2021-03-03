// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(Root);
	Mesh->SetupAttachment(Root);

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


