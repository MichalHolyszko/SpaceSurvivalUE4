// Fill out your copyright notice in the Description page of Project Settings.

#include "AICombatComponentt.h"

#include "Kismet/GameplayStatics.h"

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
    UE_LOG(LogTemp, Error, TEXT("AI COMBAT COMPONENT: TRY TO DEAL DAMAGE!"));
    if(OwnerMesh != nullptr)
	{
		FHitResult HitResult;
		bool bIsHit = SphereTrace(HitResult);

		if(bIsHit && HitResult.GetActor()->GetClass() != GetOwner()->GetClass())
		{
			UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, GetOwner()->GetInstigatorController(),  GetOwner(), nullptr);			
		}
	}
}

float UAICombatComponentt::GetAttackRange() const
{
    return AttackRange;
}