// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "PlayerControllerBase.h"
#include "PlayerCombatComponent.h"
#include "HealthComponent.h"
#include "InventoryComponent.h"
#include "QuestComponent.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	// Initialize Components
	PlayerCombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("PlayerCombatComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if(HealthComponent != nullptr)
	{
		HealthComponent->OnDeath.AddDynamic(this, &ACharacterBase::HandleDeath);
	}

	if(PlayerController != nullptr)
	{
		QuestComponent->OnPlayerEndGame.AddDynamic(PlayerController, &APlayerControllerBase::PlayerEndGame);
	}

	OnActorBeginOverlap.AddDynamic(this, &ACharacterBase::Overlapping);
	OnActorEndOverlap.AddDynamic(this, &ACharacterBase::Overlapping);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	if(PlayerInputComponent != nullptr)
	{
		PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
		PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

		PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);
		PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBase::MoveForward);

		PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACharacterBase::Interaction);

		if(PlayerCombatComponent != nullptr)
		{
			PlayerInputComponent->BindAction("ToggleWeapon", IE_Pressed, PlayerCombatComponent, &UPlayerCombatComponent::ToggleWeapon);
			PlayerInputComponent->BindAction("MeleeAttack", IE_Pressed, PlayerCombatComponent, &UPlayerCombatComponent::MeleeAttack); 
		}

		if(InventoryComponent != nullptr)
		{
			 PlayerInputComponent->BindAction(TEXT("ToggleInventory"), IE_Pressed, InventoryComponent, &UInventoryComponent::ToggleInventory);
	 	}
		
		if(QuestComponent != nullptr)
		{
			 PlayerInputComponent->BindAction(TEXT("ToggleQuest"), IE_Pressed, QuestComponent, &UQuestComponent::ToggleQuest);
			 PlayerInputComponent->BindAction(TEXT("Finish"), IE_Pressed, QuestComponent, &UQuestComponent::EndGame);
		}

		PlayerController = Cast<APlayerControllerBase>(GetController());
		if(PlayerController != nullptr)
		{
			PlayerInputComponent->BindAction(TEXT("TogglePause"), IE_Pressed, PlayerController, &APlayerControllerBase::TogglePause); 
		}
	}
}

void ACharacterBase::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACharacterBase::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ACharacterBase::Interaction()
{
	if(PlayerCombatComponent != nullptr && PlayerCombatComponent->GetPlayerStatus() == EPlayerStatus::Armed)
	{
		return;
	}
	else
	{
		TArray<AActor*> OverlappingActors;
 		GetOverlappingActors(OverlappingActors);

		for(AActor* OverllapingActor : OverlappingActors)
		{
			if(OverllapingActor != nullptr && OverllapingActor->Implements<UInteractInterface>())
			{
				IInteractInterface::Execute_Interact(OverllapingActor, this);
				break;
			}
		} 
	}
}

void ACharacterBase::Overlapping(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor != nullptr && OtherActor->Implements<UInteractInterface>())
	{
		IInteractInterface::Execute_ToggleOverlapping(OtherActor);
	}
}

void ACharacterBase::HandleDeath()
{
	OnPlayerKilled.Broadcast();

	if(PlayerController != nullptr)
    {
        PlayerController->PlayerKilled();
    }
	
	DetachFromControllerPendingDestroy();
	SetActorEnableCollision(false);
}




