// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "F_DirectionAnims.generated.h"

USTRUCT(BlueprintType)
struct TP_LOCOMOTION_API F_DirectionAnims
{
public:
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimSequence* F;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimSequence* B;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimSequence* R;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimSequence* L;
};
