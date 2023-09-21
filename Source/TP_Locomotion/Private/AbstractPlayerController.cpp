// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractPlayerController.h"

void AAbstractPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// Store a reference to the player's pawn
	//PlayerCharacter = Cast<>();
}

void AAbstractPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}
