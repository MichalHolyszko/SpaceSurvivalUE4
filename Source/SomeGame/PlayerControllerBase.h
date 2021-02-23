// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class SOMEGAME_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:

	APlayerControllerBase();

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY()
	class UUserWidget* HUD;
};
