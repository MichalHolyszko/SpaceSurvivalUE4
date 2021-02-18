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

	// Called by BT Task when Player is in Attack Range
	void Attack();

	// Called by Attack Anim Montage to fire Sphere Trace
	UFUNCTION(BlueprintCallable)
	void TryToDealDamage();

	// Returns Character Attack Range  
	float GetAttackRange() const;

private:

	// Melle Attack Animation Montage
	UPROPERTY(EditDefaultsOnly, Category = "Anims")
	class UAnimMontage* AttackMontage;

	// Character Attack Range
	UPROPERTY(EditAnywhere, Category = "Stats")
	float AttackRange;

	// Need this to fire sphere trace
	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
