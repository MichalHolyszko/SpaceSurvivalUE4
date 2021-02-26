// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "HealthComponent.h"
#include "EnemyHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOMEGAME_API UEnemyHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetHealthComp(UHealthComponent* HealthCompToSet);

protected:

	UPROPERTY(BlueprintReadWrite)
	UHealthComponent* OwnerHealthComponent;
};
