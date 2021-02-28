// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemContainer.generated.h"

UCLASS()
class SOMEGAME_API AItemContainer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemContainer();

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UDropComponent* DropComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float ActualHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 MaxQuantity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 ActualQuantity;
};
