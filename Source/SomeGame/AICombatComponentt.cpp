// Fill out your copyright notice in the Description page of Project Settings.

#include "AICombatComponentt.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UAICombatComponentt::UAICombatComponentt()
{
    PrimaryComponentTick.bCanEverTick = false;

}

void UAICombatComponentt::BeginPlay()
{
	Super::BeginPlay();
}

void UAICombatComponentt::TryToDealDamage(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
    if(OwnerMesh != nullptr)
	{
		FHitResult HitResult;
		bool bIsHit = SphereTrace(HitResult);

		if(bIsHit && HitResult.GetActor()->ActorHasTag(TEXT("Player")))
		{
			UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, GetOwner()->GetInstigatorController(),  GetOwner(), nullptr);			
		}
	}
}

bool UAICombatComponentt::SphereTrace(FHitResult &HitResult)
{
	FVector TraceStart = OwnerMesh->GetSocketLocation(TEXT("HandSocket")); 
	FVector Direction = UKismetMathLibrary::GetForwardVector(GetOwner()->GetActorRotation());
	FVector TraceEnd = TraceStart + Direction;

	return UKismetSystemLibrary::SphereTraceSingle(GetWorld(), TraceStart, TraceEnd, SphereRadius, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);
}

float UAICombatComponentt::GetAttackRange() const
{
    return AttackRange;
}