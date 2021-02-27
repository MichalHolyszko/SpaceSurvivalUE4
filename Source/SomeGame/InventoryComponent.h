// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ItemBase.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItem ItemStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnToggleInventoryDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOMEGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ToggleInventory();

	UPROPERTY(BlueprintAssignable)
	FOnToggleInventoryDelegate OnToggleInventory;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSlot> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Position;
};
