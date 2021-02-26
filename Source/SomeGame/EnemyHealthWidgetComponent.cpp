// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyHealthWidgetComponent.h"

#include "EnemyHealthWidget.h"

void UEnemyHealthWidgetComponent::BeginPlay()
{
    Super::BeginPlay();

    UHealthComponent* OwnerHealthComp = GetOwner()->FindComponentByClass<UHealthComponent>();
    UEnemyHealthWidget* EnemyHealthWidget = Cast<UEnemyHealthWidget>(GetUserWidgetObject());

    if(EnemyHealthWidget != nullptr && OwnerHealthComp != nullptr)
    {
        EnemyHealthWidget->SetHealthComp(OwnerHealthComp);
    }
}

