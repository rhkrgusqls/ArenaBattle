// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/PawnSensingComponent.h"
#include "SensingPawn.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API USensingPawn : public UPawnSensingComponent
{
	GENERATED_BODY()
	virtual void SensePawn(APawn& Pawn)override;

	float TimeHandle=0.0f;
	float TimeHandle2=10.0f;
};
