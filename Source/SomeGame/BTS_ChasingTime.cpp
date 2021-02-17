// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_ChasingTime.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTS_ChasingTime::UBTS_ChasingTime()
{
    NodeName = TEXT("Chasing Time");
}

void UBTS_ChasingTime::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
    Super::OnSearchStart(SearchData);

    ActivationTime = GetWorld()->GetTimeSeconds();
}

void UBTS_ChasingTime::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory,DeltaSeconds);

    float ActualTime = GetWorld()->GetTimeSeconds();
    float ChasingTime = ActualTime - ActivationTime;
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(BB_ChasingTime.SelectedKeyName, ChasingTime);
}
