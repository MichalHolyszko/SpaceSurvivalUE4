// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerBase.h"

#include "Blueprint/UserWidget.h"

APlayerControllerBase::APlayerControllerBase()
{
}

void APlayerControllerBase::BeginPlay()
{
    Super::BeginPlay();

    AddWidgetToViewport(HUDClass);
}

void APlayerControllerBase::TogglePause()
{
    AddWidgetToViewport(PauseMenuClass);
}

void APlayerControllerBase::PlayerKilled()
{
    UE_LOG(LogTemp, Warning, TEXT("Controller: Player Death"));

    AddWidgetToViewport(LoseScreenClass);
}

void APlayerControllerBase::PlayerEndGame()
{
     UE_LOG(LogTemp, Warning, TEXT("Controller: Player End Game"));

    AddWidgetToViewport(WinScreenClass);
}

void APlayerControllerBase::AddWidgetToViewport(class TSubclassOf<UUserWidget> WidgetClass)
{
    if(WidgetClass != nullptr)
    {
        UUserWidget* Widget = CreateWidget(this, WidgetClass);
        if(Widget != nullptr)
        {
            Widget->AddToViewport();
        }
    }
}

