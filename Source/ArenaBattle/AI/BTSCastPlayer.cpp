// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTSCastPlayer.h"
#include "AIController.h"
#include "ABAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTSCastPlayer::UBTSCastPlayer()
{
	NodeName = "SetCastPlayer";
}

void UBTSCastPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AABAIController* Controller = Cast<AABAIController>(OwnerComp.GetAIOwner());
	if(Controller)
	{
		bool IsPlayerCast = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsCasstPlayer"));
		if (IsPlayerCast)
		{
			Controller->StopAI();
			Controller->RestartAI();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CastFaile"));
	}
	

}
