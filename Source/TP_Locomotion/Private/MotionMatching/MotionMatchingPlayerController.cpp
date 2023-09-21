#include "MotionMatching/MotionMatchingPlayerController.h"
#include "MotionMatching/MotionMatchingCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AMotionMatchingPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// Store a reference to a Player's Pawn
	PlayerCharacter = Cast<AMotionMatchingCharacter>(aPawn);
	checkf(PlayerCharacter, TEXT("AMotionMatchingPlayerController derived classes should only possess AMotionMatchingCharacter derived classes"));

	// Get a reference to Enhanced Input Controller object
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Unable to get reference to the EnhancedInputComponent"));

	// Get a reference to LocalPlayer subsystem
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get a reference to EnhancedInputLocalPlayerSubsystem from LocalPlayer"));

	// Clear existing mappings from current subsystem and add current input mapping context
	checkf(InputMappingContext, TEXT("InputMappingContent was not specified"));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);

	// If valid input action was provided - bind it
	if (ActionLook)
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this,
			&AMotionMatchingPlayerController::HandleLook);
	if (ActionMove)
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this,
			&AMotionMatchingPlayerController::HandleMove);

	}
	// ...
}

void AMotionMatchingPlayerController::OnUnPossess()
{
	// Unbind all actions
	EnhancedInputComponent->ClearActionBindings();

	Super::OnUnPossess();
}

void AMotionMatchingPlayerController::HandleLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AMotionMatchingPlayerController::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	ForwardInput = MovementVector.Y;
	SideInput = MovementVector.X;

	// ON ANY INPUT-> rotate character to be relative to camera rotation
	const float InterpSpeed = 7.5f;

	FRotator NewCharacterRotator = PlayerCharacter->GetControlRotation();
	NewCharacterRotator.Pitch = 0;
	NewCharacterRotator.Roll = 0;

	if (ForwardInput || SideInput) {
		PlayerCharacter->SetActorRotation(
			FMath::RInterpTo(
				PlayerCharacter->GetActorRotation(),
				NewCharacterRotator,
				PlayerCharacter->GetDeltaTime(),
				InterpSpeed
			)
		);
	}

	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X);
}

void AMotionMatchingPlayerController::PlayerMovementInput(bool IsForwardAxis)
{
	if (IsForwardAxis)
	{

	}
}