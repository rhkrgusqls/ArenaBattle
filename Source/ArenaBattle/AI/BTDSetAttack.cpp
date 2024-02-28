// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDSetAttack.h"
#include "AIController.h"
#include "Character/ABCharacterNonPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

UBTDSetAttack::UBTDSetAttack()
{
	NodeName = "SetAttack";
}

void UBTDSetAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    UE_LOG(LogTemp, Warning, TEXT("AttackSetCheck"));

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return;
    }

    APawn* ControlledPawn = AIController->GetPawn();
    if (!ControlledPawn)
    {
        return;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return;
    }

    // Get the object from the blackboard
    AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("Target")));
    if (!TargetActor)
    {
        return;
    }

    // Get the distance between AI and the target object
    float DistanceToTarget = FVector::Dist(ControlledPawn->GetActorLocation(), TargetActor->GetActorLocation());

    // Set a threshold distance for the attack
    float AttackDistanceThreshold = 200.0f;

    // Check if the distance is below the threshold
    if (DistanceToTarget <= AttackDistanceThreshold)
    {
         OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsAttack"),true);


    }
    else
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsAttack"), false);
    }
}
