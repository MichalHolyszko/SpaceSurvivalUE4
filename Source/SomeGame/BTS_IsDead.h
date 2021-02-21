// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_IsDead.generated.h"

/**
 * 
 */
UCLASS()
class SOMEGAME_API UBTS_IsDead : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTS_IsDead();

private:

	UPROPERTY()
	class UHealthComponent* HealthComponent; 

protected:

	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
