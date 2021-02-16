// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

AEnemyAIController::AEnemyAIController()
{
    PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
}

void AEnemyAIController::BeginPlay() 
{
    Super::BeginPlay();

    EnemyStatusEnum = EEnemyStatus::Patrolling;

    if(BehaviorTree != nullptr)
    {
        RunBehaviorTree(BehaviorTree);
    }

    PerceptionComponent->OnTargetPerceptionInfoUpdated.AddDynamic(this, &AEnemyAIController::TargetPerceptionInfoUpdated);
}

void AEnemyAIController::TargetPerceptionInfoUpdated(const FActorPerceptionUpdateInfo &UpdateInfo)
{
    if(UpdateInfo.Stimulus.WasSuccessfullySensed())
    {
        EnemyStatusEnum = EEnemyStatus::Chasing;

        GetBlackboardComponent()->SetValueAsEnum(TEXT("EnemyStatus"), (int8)EnemyStatusEnum);
    }
}

