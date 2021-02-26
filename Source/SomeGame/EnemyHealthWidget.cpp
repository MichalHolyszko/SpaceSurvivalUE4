// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyHealthWidget.h"

void UEnemyHealthWidget::SetHealthComp(UHealthComponent* HealthCompToSet)
{
    if(HealthCompToSet != nullptr)
    {
        OwnerHealthComponent = HealthCompToSet;
    }
}