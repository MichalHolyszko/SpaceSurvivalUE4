// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "ItemInteractable.generated.h"

/**
 * 
 */
UCLASS()
class SOMEGAME_API AItemInteractable : public AItemBase, public IInteractInterface
{
	GENERATED_BODY()

	AItemInteractable();

	virtual void Interact_Implementation(AActor* OtherActor) override;

	virtual void ToggleOverlapping_Implementation() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UWidgetComponent* WidgetComponent;
};
