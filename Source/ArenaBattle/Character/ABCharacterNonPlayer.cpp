// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterNonPlayer.h"
#include "Engine/AssetManager.h"
#include "AI/ABAIController.h"


AABCharacterNonPlayer::AABCharacterNonPlayer()
{
	GetMesh()->SetHiddenInGame(true);

	AIControllerClass = AABAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	SensingPlayer = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	//SensingPlayer->OnSeePawn.AddDynamic(this, &AABCharacterNonPlayer::OnSeePawn);

	SensingPlayer->bOnlySensePlayers = true;
	SensingPlayer->bSeePawns = true;
	SensingPlayer->SensingInterval = 0.5f;		// Cognize Player per 0.5sec
	SensingPlayer->SetPeripheralVisionAngle(45.0f);

	//BBNPCData = AIControllerClass->
}

void AABCharacterNonPlayer::AttackHitCheck(AttackType AttackType)
{
}

void AABCharacterNonPlayer::ProcessComboCommand()
{
	Super::AAABCharacterBase::ProcessComboCommand();

}

float AABCharacterNonPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Stat->ApplyDamage(DamageAmount);

	//Dead
	//SetDead();

	return 0.0f;
}

void AABCharacterNonPlayer::SetDead()
{
	Super::SetDead();

	// 문을 열음
	//Door->SetActorRelativeRotation(FQuat::MakeFromEuler(FVector(0.0f, 0, 90)));
}

void AABCharacterNonPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ensure(NPCMeshes.Num() > 0);

	int32 RandIndex = FMath::RandRange(0, NPCMeshes.Num() - 1);
	NPCMeshesHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(NPCMeshes[RandIndex],
		FStreamableDelegate::CreateUObject(this, &AABCharacterNonPlayer::NPCMeshLoadCompleted));

	SensingPlayer->OnSeePawn.AddDynamic(this, &AABCharacterNonPlayer::OnSeePawn);

}


void AABCharacterNonPlayer::NPCMeshLoadCompleted()
{
	if (NPCMeshesHandle.IsValid())
	{
		USkeletalMesh* NPCMesh = Cast<USkeletalMesh>(NPCMeshesHandle->GetLoadedAsset());
		if (NPCMesh)
		{
			GetMesh()->SetSkeletalMesh(NPCMesh);
			GetMesh()->SetHiddenInGame(false);
		}
	}

	NPCMeshesHandle->ReleaseHandle();
}

void AABCharacterNonPlayer::OnSeePawn(APawn* SeenPawn)
{
	if (SeenPawn)
	{
		FVector SeenPawnLocation = SeenPawn->GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("NPC %s sees pawn at location %s"), *GetName(), *SeenPawnLocation.ToString());

		AABAIController* AIController = Cast<AABAIController>(GetController());
		if (AIController)
		{
			UE_LOG(LogTemp, Warning, TEXT("NPC %s sending sighting information to AIController"), *GetName());
			AIController->Seenplayer(SeenPawn);
		}
	}
}