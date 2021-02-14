// Copyright Epic Games, Inc. All Rights Reserved.

#include "SomeGameGameMode.h"
#include "SomeGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASomeGameGameMode::ASomeGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
