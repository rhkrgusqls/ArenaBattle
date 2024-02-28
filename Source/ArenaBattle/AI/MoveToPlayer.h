// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "MoveToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UMoveToPlayer : public UBTTask_MoveTo
{
	GENERATED_BODY()
	UMoveToPlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
