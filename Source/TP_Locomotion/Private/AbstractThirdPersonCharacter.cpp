// Fill out your copyright notice in the Description page of Project Settings.

#include "AbstractThirdPersonCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAbstractThirdPersonCharacter::AAbstractThirdPersonCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//// BOOM ARM
	BoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera boom"));
	BoomArm->SetupAttachment(RootComponent);
	BoomArm->TargetArmLength = 300.f;
	BoomArm->bUsePawnControlRotation = true; // TODO: TO BE REMOVED LATER ON


	//// CAMERA
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(BoomArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	// Prevent controller input from rotating character
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->RotationRate = FRotator(0, 540, 0);
}

// Called when the game starts or when spawned
void AAbstractThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAbstractThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Time from last frame
	CurrentDeltaTime = DeltaTime;

}

// Called to bind functionality to input
void AAbstractThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

