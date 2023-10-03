// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "F_GaitSettings.generated.h"

USTRUCT(BlueprintType)
struct TP_LOCOMOTION_API F_GaitSettings
{
	GENERATED_BODY();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Gait settings")
	float MaxWalkSpeed = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Gait settings")
	float MaxAcceleration = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Gait settings")
	float MaxBrakingAcceleration = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Gait settings")
	float BrakingFrictionFactor = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Gait settings")
	bool UseSeparateBrakingFriction = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Gait settings")
	float BrakingFriction = 0.f;


};
