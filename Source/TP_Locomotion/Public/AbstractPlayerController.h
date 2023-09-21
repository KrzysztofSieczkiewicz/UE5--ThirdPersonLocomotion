// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AbstractPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class UEnhancedInputComponent;
class MotionMatchingCharacter;

UCLASS()
class TP_LOCOMOTION_API AAbstractPlayerController : public APlayerController
{
	
public:
	//// INPUT ACTIONS
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionLook = nullptr;


	//// INPUT ACTION CONTEXT
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;


protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	void HandleMove();
	void HandleLook();

private:
	// Store a reference to the InputComponent cast to an EnhancedInputComponent
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	// Store a reference to the Pawn being controlled
	MotionMatchingCharacter* PlayerCharacter = nullptr;

	GENERATED_BODY()
};
