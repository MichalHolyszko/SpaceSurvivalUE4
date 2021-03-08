// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCombatComponent.h"
#include "Weapon.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Damage.h"
#include "Kismet/GameplayStatics.h"

UPlayerCombatComponent::UPlayerCombatComponent()
{   
    PrimaryComponentTick.bCanEverTick = false;

    // Initialize Components
	StimuliComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSourceComponent"));

    // Initialize variables
	PlayerStatus = EPlayerStatus::Unarmed;
}

void UPlayerCombatComponent::BeginPlay()
{
    Super::BeginPlay();

    if(WeaponClass != nullptr)
	{
		Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
		if(Weapon != nullptr)
		{
			Weapon->SetOwner(GetOwner());
			Weapon->AttachToComponent(OwnerMesh, FAttachmentTransformRules::KeepRelativeTransform,  (TEXT("HandSocket")));
			Weapon->SetActorHiddenInGame(true);
		}
	}
}

void UPlayerCombatComponent::ToggleWeapon()
{
	if(Weapon != nullptr)
	{
		if(PlayerStatus != EPlayerStatus::Armed)
		{
			Weapon->SetActorHiddenInGame(false);
			PlayerStatus = EPlayerStatus::Armed;
		}
		else
		{
			Weapon->SetActorHiddenInGame(true);
			PlayerStatus = EPlayerStatus::Unarmed;
		}
	}
}

void UPlayerCombatComponent::MeleeAttack()
{
	if(PlayerStatus != EPlayerStatus::Armed)
	{
		return;
	}
	else
	{
		Super::MeleeAttack();
	}
}

void UPlayerCombatComponent::TryToDealDamage(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
    if(OwnerMesh != nullptr)
	{
		FHitResult HitResult;
		bool bIsHit = SphereTrace(HitResult);

		if(bIsHit && HitResult.GetActor()->ActorHasTag(TEXT("Enemy")))
		{
			UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, GetOwner()->GetInstigatorController(), GetOwner(), nullptr);
			UAISense_Damage::ReportDamageEvent(GetWorld(), HitResult.GetActor(), GetOwner(), 0.f, HitResult.Location, HitResult.Location);
		}
	}
}

EPlayerStatus UPlayerCombatComponent::GetPlayerStatus() const
{
	return PlayerStatus;
}















		// double start = FPlatformTime::Seconds();
		// for(int32 i = 0; i < 100; i++)
		// {
		// 	AWeapon* newWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
		// }
		// double end = FPlatformTime::Seconds();
		// UE_LOG(LogTemp, Warning, TEXT("code executed in %f seconds."), end-start);


