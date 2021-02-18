// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_Attack.h"

#include "EnemyBase.h"
#include "AIController.h"

UBTT_Attack::UBTT_Attack()
{
    NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);
   
   Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn())->Attack();

    return EBTNodeResult::Succeeded;
}

