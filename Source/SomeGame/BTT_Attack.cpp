// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_Attack.h"
#include "AICombatComponentt.h"

#include "AIController.h"

UBTT_Attack::UBTT_Attack()
{
    NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);

    CombatComponent = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UAICombatComponentt>();
    
    if(CombatComponent != nullptr)
    {
        CombatComponent->MeleeAttack();
        return EBTNodeResult::Succeeded;
    }
    else
    {
        return EBTNodeResult::Failed;  
    }
    
}

