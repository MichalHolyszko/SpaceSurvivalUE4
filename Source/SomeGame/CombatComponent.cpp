// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatComponent.h"

#include "Weapon.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Engine/EngineTypes.h"
#include "Components/SkeletalMeshComponent.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Damage.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Initialize Components
	StimuliComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSourceComponent"));

	// Initialize variables
	Damage = 10.f;
	AttackRange = 200.f;
	SphereRadius = 25.f;
	
	PlayerStatus = EPlayerStatus::Unarmed;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if(Owner != nullptr)
	{
		OwnerMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();

		if(OwnerMesh != nullptr)
		{
			ActorsToIgnore.Add(GetOwner());
			OwnerMesh->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &UCombatComponent::TryToDealDamage);
			
			if(WeaponClass != nullptr)
			{
				Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
				if(Weapon != nullptr)
				{
					Weapon->SetOwner(Owner);
					Weapon->AttachToComponent(OwnerMesh, FAttachmentTransformRules::KeepRelativeTransform,  (TEXT("HandSocket")));
					Weapon->SetActorHiddenInGame(true);
				}
			}
		}
	}
}

void UCombatComponent::ToggleWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("ToggleWeapon"));

}

void UCombatComponent::MeleeAttack()
{
	if(OwnerMesh != nullptr && MeleeAttackMontage != nullptr)
	{
		if(!OwnerMesh->GetAnimInstance()->Montage_IsPlaying(MeleeAttackMontage))
		{
			OwnerMesh->GetAnimInstance()->Montage_Play(MeleeAttackMontage);
		}
	}
}

void UCombatComponent::TryToDealDamage(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if(OwnerMesh != nullptr)
	{
		FHitResult HitResult;
		bool bIsHit = SphereTrace(HitResult);

		if(bIsHit)
		{
			UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, GetOwner()->GetInstigatorController(),  GetOwner(), nullptr);
			UAISense_Damage::ReportDamageEvent(GetWorld(), HitResult.GetActor(), GetOwner(), 0.f, HitResult.Location, HitResult.Location);
		}
	}
}

bool UCombatComponent::SphereTrace(FHitResult &HitResult)
{
	FVector TraceStart = OwnerMesh->GetSocketLocation(TEXT("HandSocket")); 
	FVector Direction = UKismetMathLibrary::GetForwardVector(GetOwner()->GetActorRotation());
	FVector TraceEnd = TraceStart + Direction * AttackRange;

	return UKismetSystemLibrary::SphereTraceSingle(GetWorld(), TraceStart, TraceEnd, SphereRadius, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);
}


