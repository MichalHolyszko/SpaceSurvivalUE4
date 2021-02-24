// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

AEnemyAIController::AEnemyAIController()
{
    PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
    EnemyStatusEnum = EEnemyStatus::Patrol;
}

void AEnemyAIController::BeginPlay() 
{
    Super::BeginPlay();

    if(BehaviorTree != nullptr && PerceptionComponent != nullptr)
    {
        RunBehaviorTree(BehaviorTree);

        PerceptionComponent->OnTargetPerceptionInfoUpdated.AddDynamic(this, &AEnemyAIController::TargetPerceptionInfoUpdated);
    }
}

void AEnemyAIController::TargetPerceptionInfoUpdated(const FActorPerceptionUpdateInfo &UpdateInfo)
{
    if(UpdateInfo.Stimulus.WasSuccessfullySensed())
    {
        SetEnemyStatus(EEnemyStatus::Combat);
    }
}

void AEnemyAIController::SetEnemyStatus(EEnemyStatus EnemyStatusToSet)
{
    if(EnemyStatusEnum != EnemyStatusToSet)
    {
        EnemyStatusEnum = EnemyStatusToSet;
        GetBlackboardComponent()->SetValueAsEnum(TEXT("EnemyStatus"), (int8)EnemyStatusEnum);
    }
}

