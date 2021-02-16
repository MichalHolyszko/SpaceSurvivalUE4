// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */

 UENUM(BlueprintType)
 enum class EEnemyStatus : uint8 
 {
	  Patrolling,
	  Chasing,
	  Attacking,
	  Recovering
 };

/**
 * 
 */
UCLASS()
class SOMEGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public: 

	AEnemyAIController();

	UFUNCTION()
	void TargetPerceptionInfoUpdated(const FActorPerceptionUpdateInfo &UpdateInfo);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "BehaviorTree")
	class UBehaviorTree* BehaviorTree; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	EEnemyStatus EnemyStatusEnum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAIPerceptionComponent* AIPerceptionComponent;

};
