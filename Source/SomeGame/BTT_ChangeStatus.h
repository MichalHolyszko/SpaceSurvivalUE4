// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnemyAIController.h"
#include "BTT_ChangeStatus.generated.h"

/**
 * 
 */
UCLASS()
class SOMEGAME_API UBTT_ChangeStatus : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTT_ChangeStatus();

	UPROPERTY(EditAnywhere)
	EEnemyStatus NewStatus;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BB_ActualStatus;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
