// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "IsAttackSet.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UIsAttackSet : public UBTTaskNode
{
	GENERATED_BODY()
	
	UIsAttackSet();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) override;

	APawn* SetTargetPawn;

};
