// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractThirdPersonCharacter.h"
#include "MotionMatchingCharacter.generated.h"

UCLASS()
class TP_LOCOMOTION_API AMotionMatchingCharacter : public AAbstractThirdPersonCharacter
{
private:

protected:
	
public:	
	virtual void Tick(float DeltaTime) override;

	GENERATED_BODY()

};
