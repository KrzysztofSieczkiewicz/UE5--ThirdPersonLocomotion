// Fill out your copyright notice in the Description page of Project Settings.

#include "MotionMatching/MM_BaseAnimationBlueprint.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UMM_BaseAnimationBlueprint::ReceiveGaitData(E_MM_Gait GaitData)
{
	CurrentGait = GaitData;

	return false; // TODO: later - replace this with boolean confirming success of assigning gait (extend assign with e.g. cast)
}

void UMM_BaseAnimationBlueprint::NativeInitializeAnimation()
{
	// Get Pawn owner on initialization
	CharacterMovementComponentRef = Cast<APawn>(TryGetPawnOwner());
	OwningActorReference = GetOwningActor();
}

void UMM_BaseAnimationBlueprint::NativeThreadSafeUpdateAnimation(float DeltaTime)
{
	if (!CharacterMovementComponentRef) return;

	WorldLocation = OwningActorReference->GetActorLocation();
	WorldRotation = OwningActorReference->GetActorRotation();

	UCharacterMovementComponent* CharacterMovement = Cast<UCharacterMovementComponent>(
		CharacterMovementComponentRef->GetMovementComponent());
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
	LocomotionDirection = CalculateLocomotionDirection(
		LocomotionAngle,
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

	// CHECK CURRENT CHARACTER DIRECTION
	// BASED ON CURRENT AND PREVIOUS DIRECTION -> SET HIP FACING DIRECTION
	if (!(CurrentLocomotionAngle >= BMin &&
		CurrentLocomotionAngle <= BMax)) // BACKWARDS
	{
		HipDirection = E_HipFacing::B;
		return E_MM_LocomotionDirection::B;
	}

	if (CurrentLocomotionAngle >= FMin &&
		CurrentLocomotionAngle <= FMax) // FORWARD
	{
		HipDirection = E_HipFacing::F;
		return E_MM_LocomotionDirection::F;
	}
	
	if (CurrentLocomotionAngle < 0) // LEFT
	{
		switch (LocomotionDirection) {
		case E_MM_LocomotionDirection::F:
			HipDirection = E_HipFacing::F;
			break;
		case E_MM_LocomotionDirection::B:
			HipDirection = E_HipFacing::B;
			break;
		case E_MM_LocomotionDirection::R:
			HipDirection = (HipDirection == E_HipFacing::F) ? E_HipFacing::B : E_HipFacing::F;
			break;
		}
		return E_MM_LocomotionDirection::L;

	}
	else if (CurrentLocomotionAngle > 0)  // RIGHT
	{
		switch (LocomotionDirection) {
		case E_MM_LocomotionDirection::F:
			HipDirection = E_HipFacing::F;
			break;
		case E_MM_LocomotionDirection::B:
			HipDirection = E_HipFacing::B;
			break;
		case E_MM_LocomotionDirection::L:
			HipDirection = (HipDirection == E_HipFacing::F) ? E_HipFacing::B : E_HipFacing::F;
		}
		return E_MM_LocomotionDirection::R;

	}
	return E_MM_LocomotionDirection::F;
}

