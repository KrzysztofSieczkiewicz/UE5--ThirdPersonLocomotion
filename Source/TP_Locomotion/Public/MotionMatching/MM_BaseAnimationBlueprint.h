// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MM_BaseAnimationBlueprint.generated.h"

class AMotionMatchingCharacter;
//class AActor;

UCLASS()
class TP_LOCOMOTION_API UMM_BaseAnimationBlueprint : public UAnimInstance
{
public:

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

	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) override;

private:
	UPROPERTY()
	APawn* CharacterMovementCompReference = nullptr;
	UPROPERTY()
	AActor* OwningActorReference = nullptr;

	GENERATED_BODY()
	
};