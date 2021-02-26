// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class SOMEGAME_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void HandleDeath();

private:

	UPROPERTY(Editanywhere, Category = "Death")
	float DestroyDelay;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAICombatComponentt* AICombatComponentt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UEnemyHealthWidgetComponent* HealthWidgetComponent;

};
