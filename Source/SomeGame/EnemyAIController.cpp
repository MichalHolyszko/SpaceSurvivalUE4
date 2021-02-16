// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"

void AEnemyAIController::BeginPlay() 
{
    Super::BeginPlay();

    if(BehaviorTree != nullptr)
    {
        RunBehaviorTree(BehaviorTree);
    }
}

