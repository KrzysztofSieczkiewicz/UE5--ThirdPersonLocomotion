// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MotionMatching/E_MM_LocomotionDirection.h"
#include "MotionMatching/E_HipFacing.h"
#include "MotionMatching/F_LocomotionDirectionSettings.h"
#include "BPI_GaitInterface.h"
#include "MM_BaseAnimationBlueprint.generated.h"

class AMotionMatchingCharacter;

UCLASS()
class TP_LOCOMOTION_API UMM_BaseAnimationBlueprint : public UAnimInstance, public IBPI_GaitInterface
{
public:
	GENERATED_BODY()

	// GaitInterface
	virtual bool ReceiveGaitData(E_MM_Gait GaitData) override;

	UPROPERTY(BlueprintReadOnly, Category = "Character Movement")
	E_MM_Gait CurrentGait;
	UPROPERTY(BlueprintReadOnly, Category = "Character Movement")
	E_MM_LocomotionDirection LocomotionDirection;
	UPROPERTY(BlueprintReadOnly, Category = "Character Movement")
	E_HipFacing HipDirection;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Character Movement")
	bool IsRunning;

	UPROPERTY(BlueprintReadOnly, Category = "Character Movement")
	FVector CurrentAcceleration;
	UPROPERTY(BlueprintReadOnly, Category = "Character Movement")
	FVector CharacterVelocity;
	UPROPERTY(BlueprintReadOnly, Category = "Character Movement")
	FVector WorldLocation;
	UPROPERTY(BlueprintReadOnly, Category = "Character Movement")
	FRotator WorldRotation;
	UPROPERTY(BlueprintReadOnly, Category = "Character Movement")
	float LocomotionAngle;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) override;

private:
	UPROPERTY()
	APawn* CharacterMovementComponentRef = nullptr;
	UPROPERTY()
	AActor* OwningActorReference = nullptr;

	UPROPERTY()
	F_LocomotionDirectionSettings LocomotionDirectionSettings;

	UFUNCTION()
	E_MM_LocomotionDirection CalculateLocomotionDirection(float CurrentLocomotionAngle,
		E_MM_LocomotionDirection InLocomotionDirection,
		F_LocomotionDirectionSettings InLocomotionDirectionSettings);	
};