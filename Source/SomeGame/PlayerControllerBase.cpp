// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerBase.h"

#include "Blueprint/UserWidget.h"

APlayerControllerBase::APlayerControllerBase()
{
}

void APlayerControllerBase::BeginPlay()
{
    Super::BeginPlay();

    if(HUDClass != nullptr)
    {
        HUD = CreateWidget(this, HUDClass);
        if(HUD != nullptr)
        {
            HUD->AddToViewport();
        }
    }
}