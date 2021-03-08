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

	UFUNCTION()
	void PlayerEndGame();

	void TogglePause();

protected:

	virtual void BeginPlay() override;

	void AddWidgetToViewport(class TSubclassOf<UUserWidget> WidgetClass);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<UUserWidget> HUDClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<UUserWidget> LoseScreenClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<UUserWidget> WinScreenClass;
};
