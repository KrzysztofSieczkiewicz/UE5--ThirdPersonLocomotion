// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "F_GaitSettings.generated.h"

USTRUCT(BlueprintType)
struct TP_LOCOMOTION_API F_GaitSettings
{
public:
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly)
	float MaxWalkSpeed = 0.f;
	UPROPERTY(BlueprintReadOnly)
	float MaxAcceleration = 0.f;
	UPROPERTY(BlueprintReadOnly)
	float BrakingDecelerationWalking = 0.f;
	UPROPERTY(BlueprintReadOnly)
	float BrakingFrictionFactor = 0.f;
	UPROPERTY(BlueprintReadOnly)
	bool UseSeparateBrakingFriction = 0.f;
	UPROPERTY(BlueprintReadOnly)
	float BrakingFriction = 0.f;


};
