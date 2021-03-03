// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimInstance.h"
#include "Engine/EngineTypes.h"
#include "Components/SkeletalMeshComponent.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Initialize variables
	Damage = 10.f;
	AttackRange = 200.f;
	SphereRadius = 25.f;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();

	if(OwnerMesh != nullptr)
	{
		ActorsToIgnore.Add(GetOwner());
		OwnerMesh->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &UCombatComponent::TryToDealDamage);
	}
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
	
}

bool UCombatComponent::SphereTrace(FHitResult &HitResult)
{
	FVector TraceStart = OwnerMesh->GetSocketLocation(TEXT("HandSocket")); 
	FVector Direction = UKismetMathLibrary::GetForwardVector(GetOwner()->GetActorRotation());
	FVector TraceEnd = TraceStart + Direction * AttackRange;

	return UKismetSystemLibrary::SphereTraceSingle(GetWorld(), TraceStart, TraceEnd, SphereRadius, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);
}


