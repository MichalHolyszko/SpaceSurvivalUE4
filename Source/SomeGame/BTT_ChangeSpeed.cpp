// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_ChangeSpeed.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTT_ChangeSpeed::UBTT_ChangeSpeed()
{
    NodeName = TEXT("ChangeSpeed");
}

EBTNodeResult::Type UBTT_ChangeSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetAIOwner()->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = SpeedToSet;
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), SpeedToSet);

    return EBTNodeResult::Succeeded;
}

