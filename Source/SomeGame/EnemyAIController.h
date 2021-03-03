// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyAIController.generated.h"

 UENUM(BlueprintType)
 enum class EEnemyStatus : uint8 
 {
	  Patrol,
	  Combat
 };

UCLASS()
class SOMEGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public: 

	AEnemyAIController();

	// Called when perception is changed i.e when Damage was Sensed
	UFUNCTION()
	void TargetPerceptionInfoUpdated(const FActorPerceptionUpdateInfo &UpdateInfo);

	// Called to change enemy status
	void SetEnemyStatus(EEnemyStatus EnemyStatusToSet);

	// Called On Pawn Death
	UFUNCTION()
	void PawnDeath();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "BehaviorTree")
	class UBehaviorTree* BehaviorTree; 

	// Enemy Status needed to do different behaviors i.e Patrol or Combat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	EEnemyStatus EnemyStatusEnum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY()
	class UHealthComponent* HealthComponent; 
};
