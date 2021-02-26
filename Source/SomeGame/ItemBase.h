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
	bool bIsStackable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsConsumable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Thunbail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItemBase> Class;
};

UCLASS()
class SOMEGAME_API AItemBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItem ItemStruct;
};
