// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "EnemyHealthWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class SOMEGAME_API UEnemyHealthWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
};
