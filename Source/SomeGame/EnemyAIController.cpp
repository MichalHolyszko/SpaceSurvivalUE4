// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"

#include "HealthComponent.h"

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

     HealthComponent = GetPawn()->FindComponentByClass<UHealthComponent>();

    if(BehaviorTree != nullptr && PerceptionComponent != nullptr && HealthComponent)
    {
        RunBehaviorTree(BehaviorTree);

        PerceptionComponent->OnTargetPerceptionInfoUpdated.AddDynamic(this, &AEnemyAIController::TargetPerceptionInfoUpdated);
        HealthComponent->OnDeath.AddDynamic(this, &AEnemyAIController::PawnDeath);
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

void AEnemyAIController::PawnDeath()
{
    if(HealthComponent != nullptr)
    {
       GetBlackboardComponent()->SetValueAsBool(TEXT("IsDead"), true);
    }
}
  
