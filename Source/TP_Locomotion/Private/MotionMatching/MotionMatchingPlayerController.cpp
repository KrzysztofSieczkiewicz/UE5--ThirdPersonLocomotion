#include "MotionMatching/MotionMatchingPlayerController.h"
#include "MotionMatching/MotionMatchingCharacter.h"
#include "MotionMatching/E_MM_Gait.h"
#include "MotionMatching/MM_BaseAnimationBlueprint.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMotionMatchingPlayerController::AMotionMatchingPlayerController()
{
	// SET VALUES FOR GAITS
	GaitSettings.Emplace(
		E_MM_Gait::Walk,
		{
			200.f, //MaxWalkSpeed
			400.f, //MaxAcceleration
			400.f, //BrakingDecelerationWalking
			1.f, //BrakingFrictionFactor
			false, // UseSeparateBrakingFriction
			0.f //BrakingFriction
		}
	);
	GaitSettings.Emplace(
		E_MM_Gait::Run,
		{
			400.f, //MaxWalkSpeed
			800.f, //MaxAcceleration
			800.f, //BrakingDecelerationWalking
			1.f, //BrakingFrictionFactor
			false, // UseSeparateBrakingFriction
			0.f //BrakingFriction
		}
	);
}

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
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this,
			&AMotionMatchingPlayerController::HandleMove);
	if (ActionAim)
	{
		EnhancedInputComponent->BindAction(ActionAim, ETriggerEvent::Started, this,
			&AMotionMatchingPlayerController::HandleAimStarted);
		EnhancedInputComponent->BindAction(ActionAim, ETriggerEvent::Completed, this,
			&AMotionMatchingPlayerController::HandleAimCompleted);
	}
		
	// ...


	// Set default gait on possess
	UpdateGait(E_MM_Gait::Run);
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

void AMotionMatchingPlayerController::HandleAimStarted()
{
	UpdateGait(E_MM_Gait::Walk);
}

void AMotionMatchingPlayerController::HandleAimCompleted()
{
	UpdateGait(PreviousGait);
}


void AMotionMatchingPlayerController::UpdateGait(E_MM_Gait DesiredGait)
{
	if (!GaitSettings.Contains(DesiredGait))
		return;

	PreviousGait = CurrentGait;
	CurrentGait = DesiredGait;


	// Get animation instance from current player character and assign gait
	UMM_BaseAnimationBlueprint* AnimBlueprint = Cast<UMM_BaseAnimationBlueprint>(PlayerCharacter->GetMesh()->GetAnimInstance());
	AnimBlueprint->ReceiveGaitData(DesiredGait);

	// Get movement component from current player character
	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(PlayerCharacter->GetMovementComponent());
	
	// Get settings and values for current gait
	F_GaitSettings* CurrentGaitValues = GaitSettings.Find(DesiredGait);

	// Assign values to movement component
	MovementComponent->MaxWalkSpeed = CurrentGaitValues->MaxWalkSpeed;
	MovementComponent->MaxAcceleration = CurrentGaitValues->MaxAcceleration;
	MovementComponent->BrakingDecelerationWalking = CurrentGaitValues->BrakingDecelerationWalking;
	MovementComponent->BrakingFrictionFactor = CurrentGaitValues->BrakingFrictionFactor;
	MovementComponent->bUseSeparateBrakingFriction = CurrentGaitValues->UseSeparateBrakingFriction;
	MovementComponent->BrakingFriction = CurrentGaitValues->BrakingFriction;
}