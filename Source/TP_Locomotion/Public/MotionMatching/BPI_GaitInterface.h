// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MotionMatching/E_MM_Gait.h"
#include "BPI_GaitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBPI_GaitInterface : public UInterface
{
	GENERATED_BODY()
};

class TP_LOCOMOTION_API IBPI_GaitInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool ReceiveGaitData(E_MM_Gait GaitData) = 0;
};
