// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTSCastPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UBTSCastPlayer : public UBTService
{
	GENERATED_BODY()
	UBTSCastPlayer();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
