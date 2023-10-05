// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "E_MM_LocomotionDirection.h"
#include "BPI_GaitInterface.h"
#include "F_LocomotionDirectionSettings.h"
#include "MM_BaseAnimationBlueprint.generated.h"

class AMotionMatchingCharacter;

UCLASS()
class TP_LOCOMOTION_API UMM_BaseAnimationBlueprint : public UAnimInstance, public IBPI_GaitInterface
{
public:
	GENERATED_BODY()

	// GaitInterface
	virtual bool ReceiveGaitData(E_MM_Gait GaitData) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool IsRunning;

	UPROPERTY(BlueprintReadOnly, Category = "Player Input|Character Movement")
	FVector CurrentAcceleration;
	UPROPERTY(BlueprintReadOnly, Category = "Player Input|Character Movement")
	FVector CharacterVelocity;
	UPROPERTY(BlueprintReadOnly, Category = "Player Input|Character Movement")
	FVector WorldLocation;
	UPROPERTY(BlueprintReadOnly, Category = "Player Input|Character Movement")
	FRotator WorldRotation;
	UPROPERTY(BlueprintReadOnly, Category = "Player Input|Character Movement")
	float LocomotionAngle;

	UPROPERTY(BlueprintReadOnly, Category = "Player Input|Character Movement")
	E_MM_LocomotionDirection LocomotionDirection;


	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) override;

private:
	UPROPERTY()
	APawn* CharacterMovementCompReference = nullptr;
	UPROPERTY()
	AActor* OwningActorReference = nullptr;

	UPROPERTY()
	F_LocomotionDirectionSettings LocomotionDirectionSettings;

	UFUNCTION()
	E_MM_LocomotionDirection CalculateLocomotionDirection(float CurrentLocomotionAngle,
		E_MM_LocomotionDirection InLocomotionDirection,
		F_LocomotionDirectionSettings InLocomotionDirectionSettings);

	UPROPERTY()
	E_MM_Gait CurrentGait;	
};