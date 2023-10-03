#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "E_MM_Gait.h"
#include "F_GaitSettings.h"
#include "MotionMatchingCharacter.h"
#include "MotionMatchingPlayerController.generated.h"

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
	void HandleMove(const FInputActionValue& InputActionValue);

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

	// Store current gait character is using
	UPROPERTY()
	E_MM_Gait CurrentGait;
	UFUNCTION()
	void UpdateGait(E_MM_Gait DesiredGait);
	UPROPERTY()
	TMap<E_MM_Gait, F_GaitSettings> GaitSettings;
	// TODO: create constructor and initialize basic gaits - walk and run

	GENERATED_BODY()
};
