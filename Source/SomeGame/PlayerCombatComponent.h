// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatComponent.h"
#include "PlayerCombatComponent.generated.h"


 UENUM(BlueprintType)
 enum class EPlayerStatus : uint8 
 {
	  Armed,
	  Unarmed
 };


UCLASS()
class SOMEGAME_API UPlayerCombatComponent : public UCombatComponent
{
	GENERATED_BODY()

public:

	UPlayerCombatComponent();

	void ToggleWeapon();

	// Called By Anim Montage To Fire Sphere Trace
	virtual void TryToDealDamage(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload) override;

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAIPerceptionStimuliSourceComponent* StimuliComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY()
	class AWeapon* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPlayerStatus PlayerStatus;
};
