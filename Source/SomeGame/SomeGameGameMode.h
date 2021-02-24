// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SomeGameGameMode.generated.h"

UCLASS(minimalapi)
class ASomeGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ASomeGameGameMode();
	
	virtual void StartPlay() override;

	UFUNCTION()
	void PlayerKilled();

private:

	UPROPERTY()
	class ACharacterBase* PlayerPawn;
};



