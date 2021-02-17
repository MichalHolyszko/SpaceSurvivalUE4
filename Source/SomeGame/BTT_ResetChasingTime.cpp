// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_ResetChasingTime.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTT_ResetChasingTime::UBTT_ResetChasingTime()
{
    NodeName = TEXT("Reset Chasing Time");
}

 EBTNodeResult::Type UBTT_ResetChasingTime::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
 {
     Super::ExecuteTask(OwnerComp, NodeMemory);

     OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), 0.f);

     return EBTNodeResult::Succeeded;
 }