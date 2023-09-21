#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "MotionMatchingPlayerController.generated.h"

class UInputMappingContext;
class UEnhancedInputComponent;
class AMotionMatchingCharacter;

UCLASS(Abstract)
class TP_LOCOMOTION_API AMotionMatchingPlayerController : public APlayerController
{

public:
	//// INPUT ACTIONS
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputAction> ActionLook = nullptr;

	//// INPUT ACTION CONTEXT
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;


protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	void HandleLook(const FInputActionValue& InputActionValue);
	void HandleMoveTriggered(const FInputActionValue& InputActionValue);
	void HandleMoveCompleted(const FInputActionValue& InputActionValue);


private:
	// Store a reference to the InputComponent cast to an EnhancedInputComponent
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	// Store a reference to the Pawn being controlled
	UPROPERTY()
	AMotionMatchingCharacter* PlayerCharacter = nullptr;

	// Variables to keep current input value in specific directions
	UPROPERTY()
	float ForwardInput;
	UPROPERTY()
	float SideInput;


	GENERATED_BODY()
};
