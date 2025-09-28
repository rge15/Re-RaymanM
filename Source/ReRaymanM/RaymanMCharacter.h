// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RaymanMCharacter.generated.h"

struct FInputActionValue;
class UEnhancedInputComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class RERAYMANM_API ARaymanMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARaymanMCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> m_inputCmp;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> m_inputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> m_jumpInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> m_moveInputAction;

	void StartJump();
	void StopJump();

	void MoveCharacter(const FInputActionValue& Value);

	void SetupCharacterMovementCmp();
};
