// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTSPlayerPos.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UBTSPlayerPos : public UBTService
{
	GENERATED_BODY()
	
	UBTSPlayerPos();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
