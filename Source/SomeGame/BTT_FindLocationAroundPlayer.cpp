// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_FindLocationAroundPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


UBTT_FindLocationAroundPlayer::UBTT_FindLocationAroundPlayer()
{
    NodeName = TEXT("Find Location Around Player");
}

EBTNodeResult::Type UBTT_FindLocationAroundPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    FVector PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BB_PlayerLocation.SelectedKeyName);
    FVector OwnerLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();

    FVector ConeDirection = UKismetMathLibrary::GetDirectionUnitVector(PlayerLocation, OwnerLocation);
    FVector UnitVectorInCone = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(ConeDirection, 60);
    
    FVector Origin = UnitVectorInCone * DistanceFromPlayer + PlayerLocation;

    FVector TempLocation = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), Origin, 50); 
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TempLocation);

    return EBTNodeResult::Succeeded;
}