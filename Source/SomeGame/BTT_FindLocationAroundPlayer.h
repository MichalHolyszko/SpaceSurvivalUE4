// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_FindLocationAroundPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SOMEGAME_API UBTT_FindLocationAroundPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UBTT_FindLocationAroundPlayer();

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BB_PlayerLocation;

	UPROPERTY(EditAnywhere)
	float DistanceFromPlayer = 100.f;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
