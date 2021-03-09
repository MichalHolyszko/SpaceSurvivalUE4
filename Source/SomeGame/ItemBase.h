// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "InteractInterface.h"
#include "ItemBase.generated.h"

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUsable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsConsumable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsStackable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Thunbail = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItemBase> Class;

	FORCEINLINE bool operator==(const FItem &Other) const
	{
		return (Name.EqualTo(Other.Name)) && (Description.EqualTo(Other.Description)) && (bIsUsable == Other.bIsUsable) && (bIsStackable == Other.bIsStackable) && (bIsConsumable == Other.bIsConsumable) && (Thunbail == Other.Thunbail) && (Class == Other.Class);
	}
};

UCLASS()
class SOMEGAME_API AItemBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	virtual void Interact_Implementation(AActor* OtherActor) override;

	virtual void ToggleOverlapping_Implementation() override;

	bool AddToInventory(AActor* InventoryOwner, int32 ItemQuantity);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UseItem();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ToggleWidget();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItem ItemStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
