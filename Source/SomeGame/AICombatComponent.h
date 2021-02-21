// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AICombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOMEGAME_API UAICombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAICombatComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called by BT Task when Player is in Attack Range
	void Attack();

	// Called by Attack Anim Montage to fire Sphere Trace
	UFUNCTION()
	void TryToDealDamage(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	// Returns Character Attack Range  
	float GetAttackRange() const;

private:

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
	UPROPERTY(EditDefaultsOnly, Category = "Anims")
	class UAnimMontage* AttackMontage;

	// Need this to fire sphere trace
	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY()
	class USkeletalMeshComponent* OwnerMesh;

	// HitResult - OUT param
	bool SphereTrace(FHitResult &HitResult);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
