// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SensingPawn.h"

void USensingPawn::SensePawn(APawn& Pawn)
{
	Super::UPawnSensingComponent::SensePawn(Pawn);
	if (bSeePawns && ShouldCheckVisibilityOf(&Pawn))
	{
		if (CouldSeePawn(&Pawn, false))
		{
			UE_LOG(LogTemp, Warning, TEXT("GetPlayer"));
			TimeHandle = 0.0f;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("nullPlayer"));
			
			TimeHandle = TimeHandle + 0.1f;
			if(TimeHandle>=TimeHandle2)
			{
				OnSeePawn.Broadcast(nullptr);

			}
		}
	}
}

