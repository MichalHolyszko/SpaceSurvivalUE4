// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.f;
	ActualHealth = MaxHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser )
{
	UE_LOG(LogTemp, Warning, TEXT("Damage taken: %f"), Damage);
	ActualHealth = FMath::Clamp<float>(ActualHealth - Damage, 0.f, MaxHealth);
	UE_LOG(LogTemp, Error, TEXT("Health: %f"), ActualHealth);

	if(ActualHealth <= 0.f)
	{
		UE_LOG(LogTemp, Error, TEXT("I'M DEAD!"), ActualHealth);

		OnDeath.Broadcast();
	}
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



