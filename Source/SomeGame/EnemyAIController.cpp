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

    if(BehaviorTree != nullptr && PerceptionComponent != nullptr)
    {
        RunBehaviorTree(BehaviorTree);

        PerceptionComponent->OnTargetPerceptionInfoUpdated.AddDynamic(this, &AEnemyAIController::TargetPerceptionInfoUpdated);
        EnemyStatusEnum = EEnemyStatus::Patrol;
    }
}

void AEnemyAIController::TargetPerceptionInfoUpdated(const FActorPerceptionUpdateInfo &UpdateInfo)
{
    if(UpdateInfo.Stimulus.WasSuccessfullySensed())
    {
        EnemyStatusEnum = EEnemyStatus::Combat;
        GetBlackboardComponent()->SetValueAsEnum(TEXT("EnemyStatus"), (int8)EnemyStatusEnum);
    }
}

void AEnemyAIController::SetEnemyStatus(EEnemyStatus EnemyStatusToSet)
{
    EnemyStatusEnum = EnemyStatusToSet;
}

