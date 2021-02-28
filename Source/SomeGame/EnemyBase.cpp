// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBase.h"

#include "AICombatComponentt.h"
#include "HealthComponent.h"
#include "EnemyHealthWidgetComponent.h"
#include "DropComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initalize Components
	AICombatComponentt = CreateDefaultSubobject<UAICombatComponentt>(TEXT("AICombatComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	DropComponent = CreateDefaultSubobject<UDropComponent>(TEXT("DropComponent"));

	HealthWidgetComponent = CreateDefaultSubobject<UEnemyHealthWidgetComponent>(TEXT("HealthWidgetComponent"));
	HealthWidgetComponent->SetupAttachment(RootComponent);

	// Initialize variables
	DestroyDelay = 5.f;
}
// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if(HealthComponent != nullptr)
	{
		HealthComponent->OnDeath.AddDynamic(this, &AEnemyBase::HandleDeath);
	}
}	

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy Death"));
	
	if(DropComponent != nullptr)
	{
		DropComponent->DropItem();
	}

	SetActorEnableCollision(false);
	SetLifeSpan(DestroyDelay);
}






