// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MoveToPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"

UMoveToPlayer::UMoveToPlayer()
{
    bNotifyTick = true;
}

EBTNodeResult::Type UMoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}


	APawn* PlayerPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!PlayerPawn)
	{
		return EBTNodeResult::Failed;
	}

	// Move to the player
	AIController->MoveToActor(PlayerPawn);

	return EBTNodeResult::Succeeded;
}
