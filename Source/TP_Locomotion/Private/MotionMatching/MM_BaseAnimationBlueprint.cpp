// Fill out your copyright notice in the Description page of Project Settings.

#include "MotionMatching/MM_BaseAnimationBlueprint.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMM_BaseAnimationBlueprint::NativeInitializeAnimation()
{
	// Get Pawn owner on initialization
	CharacterMovementCompReference = Cast<APawn>(TryGetPawnOwner());
	OwningActorReference = GetOwningActor();
}

void UMM_BaseAnimationBlueprint::NativeThreadSafeUpdateAnimation(float DeltaTime)
{
	if (!CharacterMovementCompReference) return;

	WorldLocation = OwningActorReference->GetActorLocation();
	WorldRotation = OwningActorReference->GetActorRotation();

	UCharacterMovementComponent* CharacterMovement = Cast<UCharacterMovementComponent>(
		CharacterMovementCompReference->GetMovementComponent());
	if (CharacterMovement)
	{
		// Current acceleration
		CurrentAcceleration = CharacterMovement->GetCurrentAcceleration();
		CurrentAcceleration.Z = 0.f;
		// Velocity vector
		CharacterVelocity = CharacterMovement->Velocity;
		CharacterVelocity.Z = 0.f;
	}
	else
		CurrentAcceleration = FVector::ZeroVector;

	// If character is moving (accceleration vector is non-zero) set IsRunning;
	if (FMath::Abs(CurrentAcceleration.Size()) > 1e-3)
		IsRunning = true;
	else
		IsRunning = false;

	// Calculate locomotion angle
	LocomotionAngle = CalculateDirection(CharacterVelocity, WorldRotation);

	// Calculate and set movement direction
	LocomotionDirection = CalculateLocomotionDirection(LocomotionAngle,
		LocomotionDirection,
		LocomotionDirectionSettings);
}

E_MM_LocomotionDirection UMM_BaseAnimationBlueprint::CalculateLocomotionDirection(float CurrentLocomotionAngle,
	E_MM_LocomotionDirection InLocomotionDirection,
	F_LocomotionDirectionSettings InLocomotionDirectionSettings)
{
	// retrieve local vars from settings struct
	float FMax = InLocomotionDirectionSettings.FMax;
	float FMin = InLocomotionDirectionSettings.FMin;
	float BMax = InLocomotionDirectionSettings.BMax;
	float BMin = InLocomotionDirectionSettings.BMin;
	float DeadZone = InLocomotionDirectionSettings.DeadZone;


	// Account for deadzone so animBP is not jumping between animations with slight camera movements
	switch (InLocomotionDirection) {
	case E_MM_LocomotionDirection::F:
		if (CurrentLocomotionAngle <= FMax + DeadZone &&
			CurrentLocomotionAngle >= FMin - DeadZone)
			return E_MM_LocomotionDirection::F;
		break;

	case E_MM_LocomotionDirection::B:
		if (!
			(CurrentLocomotionAngle <= BMax - DeadZone &&
			CurrentLocomotionAngle >= BMin + DeadZone))
			return E_MM_LocomotionDirection::B;
		break;

	case E_MM_LocomotionDirection::R:
		if (CurrentLocomotionAngle <= BMax + DeadZone &&
			CurrentLocomotionAngle >= FMax - DeadZone)
			return E_MM_LocomotionDirection::R;
		break;

	case E_MM_LocomotionDirection::L:
		if (CurrentLocomotionAngle <= FMin + DeadZone &&
			CurrentLocomotionAngle >= BMin - DeadZone)
			return E_MM_LocomotionDirection::L;
		break;

	}

	// Is character moving backwards?
	if (!(CurrentLocomotionAngle >= BMin &&
		CurrentLocomotionAngle <= BMax))
		return E_MM_LocomotionDirection::B;

	// Forward?
	if (CurrentLocomotionAngle >= FMin &&
		CurrentLocomotionAngle <= FMax)
		return E_MM_LocomotionDirection::F;

	// Left?
	if (CurrentLocomotionAngle < 0)
		return E_MM_LocomotionDirection::L;
	else
		return E_MM_LocomotionDirection::R;
	
}

