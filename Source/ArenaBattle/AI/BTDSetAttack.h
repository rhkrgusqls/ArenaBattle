// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTDSetAttack.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UBTDSetAttack : public UBTService
{
	GENERATED_BODY()
	UBTDSetAttack();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
