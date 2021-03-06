// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestComponent.h"
#include "ItemBase.h"

// Sets default values for this component's properties
UQuestComponent::UQuestComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bAllQuestsCompleted = false;
}

void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UQuestComponent::ToggleQuest()
{
	OnToggleQuest.Broadcast();
}

void UQuestComponent::EndGame()
{
	if(bAllQuestsCompleted)
	{
		OnPlayerEndGame.Broadcast();
	}
}

