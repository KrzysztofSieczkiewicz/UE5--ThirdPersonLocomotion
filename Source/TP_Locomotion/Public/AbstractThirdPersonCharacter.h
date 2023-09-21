// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbstractThirdPersonCharacter.generated.h"

// Forward declarations
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TP_LOCOMOTION_API AAbstractThirdPersonCharacter : public ACharacter
{
private:
	UPROPERTY()
	float CurrentDeltaTime;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,
		meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* BoomArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,
		meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this character's properties
	AAbstractThirdPersonCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetDeltaTime() {
		return CurrentDeltaTime;
	}

	GENERATED_BODY()

};
