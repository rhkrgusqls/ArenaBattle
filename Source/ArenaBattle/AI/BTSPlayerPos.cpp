// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTSPlayerPos.h"
#include "ABAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"

UBTSPlayerPos::UBTSPlayerPos()
{
	NodeName = "SetPlayerPos";
}

void UBTSPlayerPos::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Get the AI controller
    AController* Controller = OwnerComp.GetAIOwner();

    if (Controller)
    {
        // Get the controlled pawn
        APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

        if (TargetPawn)
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPos"), TargetPawn->GetActorLocation());
        }
    }

    
}
