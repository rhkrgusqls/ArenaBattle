// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/IsAttackSet.h"
#include "AIController.h"
#include "Character/ABCharacterNonPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UIsAttackSet::UIsAttackSet()
{
}

EBTNodeResult::Type UIsAttackSet::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}
	AABCharacterNonPlayer* AttackingPawn = Cast<AABCharacterNonPlayer>(ControllingPawn);
	if (nullptr != ControllingPawn)
	{
		AttackingPawn->ProcessComboCommand();
		return EBTNodeResult::Succeeded;
	}
	else 
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;

}
