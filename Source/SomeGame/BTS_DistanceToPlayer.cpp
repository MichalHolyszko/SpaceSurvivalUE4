// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_DistanceToPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTS_DistanceToPlayer::UBTS_DistanceToPlayer()
{
    NodeName = TEXT("DistanceToPlayer");
}

void UBTS_DistanceToPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    OwnerComp.GetBlackboardComponent()->ClearValue(BB_DistanceToPlayer.SelectedKeyName);
    float DistanceToPlayer = OwnerComp.GetAIOwner()->GetPawn()->GetDistanceTo(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(BB_DistanceToPlayer.SelectedKeyName, DistanceToPlayer);
}
