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
	mutable bool IsRunning;

	UPROPERTY(BlueprintReadOnly, Category = "Player Input|Character Movement|Acceleration")
	mutable FVector CurrentAcceleration;
	UPROPERTY(BlueprintReadOnly, Category = "Player Input|Character Movement|Location")
	mutable FVector WorldLocation;
	UPROPERTY(BlueprintReadOnly, Category = "Player Input|Character Movement|Rotation")
	mutable FRotator WorldRotation;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) override;

private:
	UPROPERTY()
	APawn* CharacterMovementCompReference = nullptr;

	UPROPERTY()
	AActor* OwningActorReference = nullptr;

	GENERATED_BODY()
	
};