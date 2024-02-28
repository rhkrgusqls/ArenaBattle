// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ABAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

AABAIController::AABAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Game/ArenaBattle/AI/BB_ABCharacter.BB_ABCharacter"));
	if (BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Game/ArenaBattle/AI/BT_ABCharacter.BT_ABCharacter"));
	if (BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}


void AABAIController::RunAI()
{
	UBlackboardComponent* BlackBoardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackBoardPtr))
	{
		Blackboard->SetValueAsVector(TEXT("SpawnPos"), GetPawn()->GetActorLocation());

		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void AABAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
	
}

void AABAIController::Seenplayer(APawn* SeenPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("See"));
	UBlackboardComponent* BlackBoardPtr = Blackboard.Get();
	if (SeenPawn != nullptr)
	{
		if (UseBlackboard(BBAsset, BlackBoardPtr))
		{
			Blackboard->SetValueAsBool(TEXT("IsCastPlayer"), true);
			Blackboard->SetValueAsObject(TEXT("Target"), SeenPawn);
			bool RunResult = RunBehaviorTree(BTAsset);
			ensure(RunResult);
			TargetPawn = SeenPawn;
		}
	}
	else
	{
		if (UseBlackboard(BBAsset, BlackBoardPtr))
		{
			Blackboard->SetValueAsBool(TEXT("IsCastPlayer"), false);
		}
	}
}

void AABAIController::RestartAI()
{
	RunBehaviorTree(BTAsset);
}
