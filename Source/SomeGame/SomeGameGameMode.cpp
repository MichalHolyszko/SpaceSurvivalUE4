// Copyright Epic Games, Inc. All Rights Reserved.

#include "SomeGameGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

#include "EnemyAIController.h"
#include "CharacterBase.h"
#include "EngineUtils.h"
#include "CharacterBase.h"
#include "PlayerControllerBase.h"

ASomeGameGameMode::ASomeGameGameMode()
{
  
}

void ASomeGameGameMode::StartPlay()
{
    Super::StartPlay();
    
    PlayerPawn = Cast<ACharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if(PlayerPawn != nullptr)
    {
        PlayerPawn->OnPlayerKilled.AddDynamic(this, &ASomeGameGameMode::PlayerKilled);
    }

}

void ASomeGameGameMode::PlayerKilled()
{
    for(AEnemyAIController* Controller : TActorRange<AEnemyAIController>(GetWorld()))
    {
        if(Controller != nullptr)
        {
            Controller->SetEnemyStatus(EEnemyStatus::Patrol);
        }
    }
    if(PlayerPawn != nullptr)
    {
        APlayerControllerBase* PlayerController = Cast<APlayerControllerBase>(PlayerPawn->GetController());
        if(PlayerController != nullptr)
        {
            PlayerController->PlayerKilled();
        }
    }
}
