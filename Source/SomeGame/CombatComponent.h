// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOMEGAME_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

	// Called By Anim Montage To Fire Sphere Trace
	UFUNCTION()
	virtual void TryToDealDamage(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	// Called by Player to execute melle attack
	virtual void MeleeAttack();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	// HitResult - OUT param
	virtual bool SphereTrace(FHitResult &HitResult);

	// Character Damage Per Hit
	UPROPERTY(EditAnywhere, Category = "Stats")
	float Damage;

	// Character Attack Range
	UPROPERTY(EditAnywhere, Category = "Stats")
	float AttackRange;

	// Character Attack Range
	UPROPERTY(EditAnywhere, Category = "Stats")
	float SphereRadius;

	// Melle Attack Animation Montage
	UPROPERTY(EditDefaultsOnly,  Category = "Anims")
	class UAnimMontage* MeleeAttackMontage;

	// Need this to fire sphere trace
	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;
	
	UPROPERTY()
	class USkeletalMeshComponent* OwnerMesh;
};
