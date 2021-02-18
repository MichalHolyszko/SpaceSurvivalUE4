// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_IsPlayerInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class SOMEGAME_API UBTS_IsPlayerInAttackRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTS_IsPlayerInAttackRange();

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BB_OwnerRange;

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
