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
	UE_LOG(LogTemp, Warning, TEXT("AttackSet"));

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}
	AABCharacterNonPlayer* AttackingPawn = Cast<AABCharacterNonPlayer>(ControllingPawn);
	if (nullptr != ControllingPawn)
	{
		APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
		if (TargetPawn)
		{
			FVector LookAtDirection = TargetPawn->GetActorLocation() - AttackingPawn->GetActorLocation();
			LookAtDirection.Z = 0.0f; // Ignore vertical component
			LookAtDirection.Normalize();

			FRotator NewRotation = FRotationMatrix::MakeFromX(LookAtDirection).Rotator();
			AttackingPawn->SetActorRotation(FMath::RInterpTo(AttackingPawn->GetActorRotation(), NewRotation, GetWorld()->GetDeltaSeconds(), 5.0f));
		}
		AttackingPawn->ProcessComboCommand();
		return EBTNodeResult::Succeeded;
	}
	else 
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;

}
