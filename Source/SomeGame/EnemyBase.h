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

	void Attack();

	UFUNCTION(BlueprintCallable)
	void TraceToHit();

	float GetAttackRange() const;

	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Anims")
	class UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float AttackRange;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
