// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_IsPlayerInAttackRange.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTS_IsPlayerInAttackRange::UBTS_IsPlayerInAttackRange()
{
    NodeName = TEXT("IsPlayerInRange");
}

void UBTS_IsPlayerInAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    float DistanceToPlayer = OwnerComp.GetAIOwner()->GetPawn()->GetDistanceTo(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    float AttackRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BB_OwnerRange.SelectedKeyName);

    bool bPlayerInAttackRange = DistanceToPlayer <= AttackRange;
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), bPlayerInAttackRange);
}