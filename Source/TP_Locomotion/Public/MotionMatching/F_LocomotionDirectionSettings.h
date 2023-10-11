// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "F_LocomotionDirectionSettings.generated.h"

USTRUCT(BlueprintType)
struct TP_LOCOMOTION_API F_LocomotionDirectionSettings
{
	GENERATED_BODY();

public: 
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Direction Settings")
	float FMin = -65.f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Direction Settings")
	float FMax = 65.f;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Direction Settings")
	float BMin = -115.f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Direction Settings")
	float BMax = 115.f;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Direction Settings")
	float DeadZone = 10.f;
};
