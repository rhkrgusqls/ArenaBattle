// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/IsAttackSet.h"
#include "AIController.h"
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

	FVector TargetPos;
	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	SetTargetPawn = TargetPawn;
	if (nullptr != SetTargetPawn)
	{
        if (false/**/)
        {
            // Distance is less than or equal to 100, perform attack
			UE_LOG(LogTemp, Warning, TEXT("IsAttack"));
            return EBTNodeResult::Succeeded;
        }

        return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;

}
