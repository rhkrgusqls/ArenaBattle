// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SetPosTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

USetPosTarget::USetPosTarget()
{
}

EBTNodeResult::Type USetPosTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		TargetPos = SetTargetPawn->GetActorLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPos"),
			TargetPos);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;

}
