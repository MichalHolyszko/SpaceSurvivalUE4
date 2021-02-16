// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_FindRandomLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTT_FindRandomLocation::UBTT_FindRandomLocation()
{
    NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UBTT_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    FVector Origin = OwnerComp.GetOwner()->GetActorLocation();
    FVector TargetLocation = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), Origin, 1000.f);

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);

    return EBTNodeResult::Succeeded;
}