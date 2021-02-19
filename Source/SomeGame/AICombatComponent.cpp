// Fill out your copyright notice in the Description page of Project Settings.

#include "AICombatComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/EngineTypes.h"

// Sets default values for this component's properties
UAICombatComponent::UAICombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Initialize Attack Range variable
	AttackRange = 200.f;
}

// Called when the game starts
void UAICombatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	ActorsToIgnore.Add(GetOwner());

	if(OwnerMesh != nullptr)
	{
		OwnerMesh->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &UAICombatComponent::TryToDealDamage);
	}
}

// Called every frame
void UAICombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
void UAICombatComponent::Attack()
{
	if(OwnerMesh !=  nullptr && AttackMontage != nullptr )
	{
		OwnerMesh->GetAnimInstance()->Montage_Play(AttackMontage);
		UE_LOG(LogTemp, Error, TEXT("Enemy ATTACK!"));
	}
}

void UAICombatComponent::TryToDealDamage(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if(OwnerMesh != nullptr)
	{
		FVector TraceStart = OwnerMesh->GetSocketLocation(TEXT("HandSocket")); 
		FVector Direction = UKismetMathLibrary::GetForwardVector(GetOwner()->GetActorRotation());
		FVector TraceEnd = TraceStart + Direction * AttackRange;
		FHitResult HitResult;

		bool bIsHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), TraceStart, TraceEnd, 25.f, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);

		if(bIsHit)
		{
			UE_LOG(LogTemp, Error, TEXT("Player HITTED!"));
		}
	}
}

float UAICombatComponent::GetAttackRange() const
{
	return AttackRange;
}


