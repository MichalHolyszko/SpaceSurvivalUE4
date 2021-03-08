// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatComponent.h"
#include "AICombatComponentt.generated.h"

/**
 * 
 */
UCLASS()
class SOMEGAME_API UAICombatComponentt : public UCombatComponent
{
	GENERATED_BODY()

public:

	UAICombatComponentt();

	// Called By Anim Montage To Fire Sphere Trace
	virtual void TryToDealDamage(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload) override;

	// Returns Character Attack Range  
	float GetAttackRange() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// HitResult - OUT param
	virtual bool SphereTrace(FHitResult &HitResult) override;
	
};
