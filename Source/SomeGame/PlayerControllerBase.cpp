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

void APlayerControllerBase::TogglePause()
{
    if(PauseMenuClass != nullptr)
    {
        PauseMenu = CreateWidget(this, PauseMenuClass);
        if(PauseMenu != nullptr)
        {
            PauseMenu->AddToViewport();
        }
    }
}

void APlayerControllerBase::PlayerKilled()
{
    UE_LOG(LogTemp, Warning, TEXT("Controller: Player Death"));

     if(HUD != nullptr)
     {
        HUD->RemoveFromViewport();
    }

    if(LoseScreenClass != nullptr)
    {
        LoseScreen = CreateWidget(this, LoseScreenClass);
        if(LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }
}