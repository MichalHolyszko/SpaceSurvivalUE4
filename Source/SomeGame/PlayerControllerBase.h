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

	void PlayerKilled();

	void TogglePause();

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY()
	class UUserWidget* HUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY()
	class UUserWidget* PauseMenu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<UUserWidget> LoseScreenClass;

	UPROPERTY()
	class UUserWidget* LoseScreen;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<UUserWidget> WinScreenClass;

	UPROPERTY()
	class UUserWidget* WinScreen;
};
