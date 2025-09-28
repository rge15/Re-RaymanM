// Fill out your copyright notice in the Description page of Project Settings.


#include "RaymanMCharacter.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/InputActionValue.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARaymanMCharacter::ARaymanMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARaymanMCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (auto* playerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* inputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			if (m_inputMapping)
			{
				inputSystem->AddMappingContext(m_inputMapping, 0);
			}
		}
	}

	SetupCharacterMovementCmp();
}

void ARaymanMCharacter::SetupCharacterMovementCmp()
{
	//UCharacterMovementComponent& charMovCmp = GetCharacterMovement();
	// Jump settings

}

// Called every frame
void ARaymanMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARaymanMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	m_inputCmp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (m_jumpInputAction)
	{
		m_inputCmp->BindAction(m_jumpInputAction, ETriggerEvent::Started, this, &ARaymanMCharacter::StartJump);
		m_inputCmp->BindAction(m_jumpInputAction, ETriggerEvent::Completed, this, &ARaymanMCharacter::StopJump);
	}

	if (m_moveInputAction)
	{
		m_inputCmp->BindAction(m_moveInputAction, ETriggerEvent::Triggered, this, &ARaymanMCharacter::MoveCharacter);
	}

}

void ARaymanMCharacter::StartJump()
{
	Jump();
}

void ARaymanMCharacter::StopJump()
{
	StopJumping();
	if (GetCharacterMovement()->Velocity.Z > 0.f)
	{
		GetCharacterMovement()->Velocity.Z = 0.f;
	}
}

void ARaymanMCharacter::MoveCharacter(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();

	const FVector ActorFwdVector = GetActorForwardVector();
	const FVector ActorRightVector = GetActorRightVector();

	AddMovementInput(ActorFwdVector, MovementValue.Y);
	AddMovementInput(ActorRightVector, MovementValue.X);
}

