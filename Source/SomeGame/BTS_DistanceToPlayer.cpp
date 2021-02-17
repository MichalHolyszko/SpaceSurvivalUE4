// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_DistanceToPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTS_DistanceToPlayer::UBTS_DistanceToPlayer()
{
    NodeName = TEXT("DistanceToPlayer");
}

void UBTS_DistanceToPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    FVector PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BB_PlayerLocation.SelectedKeyName);
    FVector OwnerLocation = OwnerComp.GetOwner()->GetActorLocation();
    float DistanceToPlayer = UKismetMathLibrary::Vector_Distance(PlayerLocation, OwnerLocation); 

    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(BB_DistanceToPlayer.SelectedKeyName, DistanceToPlayer);
}
