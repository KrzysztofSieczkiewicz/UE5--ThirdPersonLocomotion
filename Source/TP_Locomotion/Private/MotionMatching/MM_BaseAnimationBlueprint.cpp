// Fill out your copyright notice in the Description page of Project Settings.

#include "MotionMatching/MM_BaseAnimationBlueprint.h"
#include "GameFramework/CharacterMovementComponent.h"


void UMM_BaseAnimationBlueprint::NativeThreadSafeUpdateAnimation(float DeltaTime) const
{
	WorldLocation = GetOwningActor()->GetActorLocation();
	WorldRotation = GetOwningActor()->GetActorRotation();

	UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();
	if (CharacterMovement)
	{
		CurrentAcceleration = CharacterMovement->GetCurrentAcceleration();
	}
	else
	{
		CurrentAcceleration = FVector::ZeroVector;
	}
}

UCharacterMovementComponent* UMM_BaseAnimationBlueprint::GetCharacterMovement() const
{
	// Get current pawn owner. If it's not a character, return nullptr
	return Cast<UCharacterMovementComponent>(
		TryGetPawnOwner()->GetMovementComponent());
}

