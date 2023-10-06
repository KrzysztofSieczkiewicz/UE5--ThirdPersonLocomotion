// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractThirdPersonCharacter.h"
#include "MotionMatching/E_MM_Gait.h"
#include "MotionMatching/F_GaitSettings.h"
#include "MotionMatchingCharacter.generated.h"

UCLASS()
class TP_LOCOMOTION_API AMotionMatchingCharacter : public AAbstractThirdPersonCharacter
{
public:
	GENERATED_BODY()

	AMotionMatchingCharacter();

	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateGait(E_MM_Gait DesiredGait);

	// Store current gait character is using and previous (allows for 'return to previous state')
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement")
	E_MM_Gait PreviousGait;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement")
	E_MM_Gait CurrentGait;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement")
	TMap<E_MM_Gait, F_GaitSettings> GaitSettings;


protected:
	

private:
	

};
