// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "E_MM_LocomotionDirection.generated.h"

UENUM(BlueprintType)
enum class E_MM_LocomotionDirection : uint8
{
    F        UMETA(DisplayName = "Forward"),
    B        UMETA(DisplayName = "Backward"),
    R        UMETA(DisplayName = "Right"),
    L        UMETA(DisplayName = "Left"),
};
