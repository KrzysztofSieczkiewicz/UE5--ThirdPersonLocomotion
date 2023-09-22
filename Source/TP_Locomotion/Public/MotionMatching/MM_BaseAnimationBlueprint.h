// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MM_BaseAnimationBlueprint.generated.h"

class AMotionMatchingCharacter;

UCLASS()
class TP_LOCOMOTION_API UMM_BaseAnimationBlueprint : public UAnimInstance
{
public:

protected:
	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCharacterMovementComponent* GetCharacterMovement() const;

private: 
	UPROPERTY(EditDefaultsOnly, Category = "Player Input|Character Movement|Acceleration")
	mutable FVector CurrentAcceleration;
	UPROPERTY(EditDefaultsOnly, Category = "Player Input|Character Movement|Location")
	mutable FVector WorldLocation;
	UPROPERTY(EditDefaultsOnly, Category = "Player Input|Character Movement|Rotation")
	mutable FRotator WorldRotation;

	GENERATED_BODY()
	
};
