// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"

USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AItemBase> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnToggleQuestDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerEndGame);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOMEGAME_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestComponent();

	void ToggleQuest();

	UPROPERTY(BlueprintAssignable)
	FOnToggleQuestDelegate OnToggleQuest;

	void EndGame();

	UPROPERTY()
	FOnPlayerEndGame OnPlayerEndGame;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuest> Quests; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Position;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bAllQuestsCompleted;
};
