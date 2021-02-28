// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Initialize default variables values
	MaxHealth = 100.f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	ActualHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser )
{
	ActualHealth = FMath::Clamp<float>(ActualHealth - Damage, 0.f, MaxHealth);

	if(IsDead())
	{
		OnDeath.Broadcast();
	}
}

void UHealthComponent::RestoreHealth(float HealthPoints)
{
	ActualHealth = FMath::Clamp<float>(ActualHealth + HealthPoints, 0.f, MaxHealth);
}

bool UHealthComponent::IsDead() const
{
	return ActualHealth <= 0.f;
}

float UHealthComponent::GetHealthPercent() const
{
	// !!! Max Health must be != 0 (dividing by 0) 
	return ActualHealth / MaxHealth;
}

float UHealthComponent::GetActualHealth() const
{
	return ActualHealth;
}



