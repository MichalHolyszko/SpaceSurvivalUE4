// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_ChasingTime.generated.h"

/**
 * 
 */
UCLASS()
class SOMEGAME_API UBTS_ChasingTime : public UBTService
{
	GENERATED_BODY()

public:

	UBTS_ChasingTime();

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BB_ChasingTime;

private:

	float ActivationTime;

protected:

	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
