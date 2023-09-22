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

	// Handle acceleration
	UCharacterMovementComponent* CharacterMovement = Cast<UCharacterMovementComponent>(
		CharacterMovementCompReference->GetMovementComponent());
	if (CharacterMovement)
	{
		CurrentAcceleration = CharacterMovement->GetCurrentAcceleration();
		CurrentAcceleration.Z = 0.f;
	}
	else
		CurrentAcceleration = FVector::ZeroVector;

	// If character is moving (accceleration vector is non-zero) set IsRunning;
	if (FMath::Abs(CurrentAcceleration.Size()) > 1e-3)
		IsRunning = true;
	else
		IsRunning = false;
}

