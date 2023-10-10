// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "E_HipFacing.generated.h"

UENUM(BlueprintType)
enum class E_HipFacing : uint8
{
	F    UMETA(DisplayName = "Front"),
	B    UMETA(DisplayName = "Back"),
};
