// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_IsPlayerInAttackRange.h"
#include "AICombatComponentt.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTS_IsPlayerInAttackRange::UBTS_IsPlayerInAttackRange()
{
    NodeName = TEXT("IsPlayerInRange");
}

void UBTS_IsPlayerInAttackRange::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
    MyPawn = SearchData.OwnerComp.GetAIOwner()->GetPawn();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(MyPawn != nullptr)
    {
        CombatComponent = MyPawn->FindComponentByClass<UAICombatComponentt>();
    }
}

void UBTS_IsPlayerInAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if(CombatComponent != nullptr && MyPawn != nullptr)
    {
        float DistanceToPlayer = MyPawn->GetDistanceTo(PlayerPawn);
        float AttackRange = CombatComponent->GetAttackRange();
        bool bPlayerInAttackRange = DistanceToPlayer <= AttackRange;

        OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), bPlayerInAttackRange);
    }
}