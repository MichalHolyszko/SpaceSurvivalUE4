// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Attack.generated.h"

/**
 * 
 */
UCLASS()
class SOMEGAME_API UBTT_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTT_Attack();

private:

	UPROPERTY()
	class UAICombatComponentt* CombatComponent;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
