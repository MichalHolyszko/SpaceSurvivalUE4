// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_ChangeStatus.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTT_ChangeStatus::UBTT_ChangeStatus()
{
    NodeName = TEXT("Change Status");
}

EBTNodeResult::Type UBTT_ChangeStatus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

    if(AIController != nullptr)
    {
        AIController->SetEnemyStatus(NewStatus);
        OwnerComp.GetBlackboardComponent()->SetValueAsEnum(BB_ActualStatus.SelectedKeyName, (uint8)NewStatus);
        return EBTNodeResult::Succeeded;
    }
    else
    {
         return EBTNodeResult::Failed;
    }
}

