// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBase.h"

#include "Animation/AnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/EngineTypes.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Attack Range variable
	AttackRange = 200.f;

}
// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::Attack()
{
	if(AttackMontage != nullptr)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
		UE_LOG(LogTemp, Error, TEXT("Enemy ATTACK!"));
	}
}

float AEnemyBase::GetAttackRange() const
{
	return AttackRange;
}

void AEnemyBase::TryToDealDamage()
{
	FVector TraceStart = GetMesh()->GetSocketLocation(TEXT("HandSocket")); 
	FVector Direction = UKismetMathLibrary::GetForwardVector(GetActorRotation());
	FVector TraceEnd = TraceStart + Direction * AttackRange;
	FHitResult HitResult;

	bool bIsHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), TraceStart, TraceEnd, 25.f, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);

	if(bIsHit)
	{
		UE_LOG(LogTemp, Error, TEXT("Player HITTED!"));
	}
}



