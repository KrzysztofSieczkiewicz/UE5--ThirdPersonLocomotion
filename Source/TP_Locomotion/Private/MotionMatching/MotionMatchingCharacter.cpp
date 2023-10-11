// Fill out your copyright notice in the Description page of Project Settings.

#include "MotionMatching/MotionMatchingCharacter.h"
#include "MotionMatching/E_MM_Gait.h"
#include "MotionMatching/MM_BaseAnimationBlueprint.h"
#include "GameFramework/CharacterMovementComponent.h"

AMotionMatchingCharacter::AMotionMatchingCharacter()
{
	// TODO: CONSIDER MOVING GAIT TO BLUEPRINT CLASSES

	// SET VALUES FOR GAITS
	GaitSettings.Emplace(
		E_MM_Gait::Walk,
		{
			200.f, //MaxWalkSpeed
			400.f, //MaxAcceleration
			400.f, //BrakingDecelerationWalking
			1.f, //BrakingFrictionFactor
			false, // UseSeparateBrakingFriction
			0.f //BrakingFriction
		}
	);
	GaitSettings.Emplace(
		E_MM_Gait::Run,
		{
			600.f, //MaxWalkSpeed
			800.f, //MaxAcceleration
			800.f, //BrakingDecelerationWalking
			1.f, //BrakingFrictionFactor
			false, // UseSeparateBrakingFriction
			0.f //BrakingFriction
		}
	);
}

void AMotionMatchingCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set default gait on game start
	UpdateGait(E_MM_Gait::Run);
}

void AMotionMatchingCharacter::UpdateGait(E_MM_Gait DesiredGait)
{
	if (!GaitSettings.Contains(DesiredGait))
		return;

	PreviousGait = CurrentGait;
	CurrentGait = DesiredGait;


	// Get animation instance from current player character and assign gait
	UMM_BaseAnimationBlueprint* AnimBlueprint = Cast<UMM_BaseAnimationBlueprint>(GetMesh()->GetAnimInstance());
	AnimBlueprint->ReceiveGaitData(DesiredGait);

	// Get movement component from current player character
	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	// Get settings and values for current gait
	F_GaitSettings* CurrentGaitValues = GaitSettings.Find(DesiredGait);

	// Assign values to movement component
	MovementComponent->MaxWalkSpeed = CurrentGaitValues->MaxWalkSpeed;
	MovementComponent->MaxAcceleration = CurrentGaitValues->MaxAcceleration;
	MovementComponent->BrakingDecelerationWalking = CurrentGaitValues->BrakingDecelerationWalking;
	MovementComponent->BrakingFrictionFactor = CurrentGaitValues->BrakingFrictionFactor;
	MovementComponent->bUseSeparateBrakingFriction = CurrentGaitValues->UseSeparateBrakingFriction;
	MovementComponent->BrakingFriction = CurrentGaitValues->BrakingFriction;
}
