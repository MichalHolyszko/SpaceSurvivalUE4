// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_IsDead.h"
#include "HealthComponent.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_IsDead::UBTS_IsDead()
{
    NodeName = TEXT("IsDead");
}

void UBTS_IsDead::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
    Super::OnSearchStart(SearchData);

    HealthComponent = SearchData.OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UHealthComponent>();
}

void UBTS_IsDead::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if(HealthComponent != nullptr)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), HealthComponent->IsDead());
    }
}
