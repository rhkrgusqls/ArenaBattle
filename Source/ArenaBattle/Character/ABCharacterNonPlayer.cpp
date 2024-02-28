// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterNonPlayer.h"
#include "Engine/AssetManager.h"
#include "AI/ABAIController.h"
#include "ABComboAttackDataAsset.h"
#include "Components/SensingPawn.h"
#include "Perception/AIPerceptionComponent.h"


AABCharacterNonPlayer::AABCharacterNonPlayer()
{
	GetMesh()->SetHiddenInGame(true);

	AIControllerClass = AABAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	SensingPlayer = CreateDefaultSubobject<USensingPawn>(TEXT("PawnSensingComponent"));
	//SensingPlayer->OnSeePawn.AddDynamic(this, &AABCharacterNonPlayer::OnSeePawn);

	SensingPlayer->bOnlySensePlayers = true;
	SensingPlayer->bSeePawns = true;
	SensingPlayer->SensingInterval = 0.1f;
	SensingPlayer->SetPeripheralVisionAngle(45.0f);

	static ConstructorHelpers::FObjectFinder<UABComboAttackDataAsset> ComboActionDataRef(TEXT("/Game/ArenaBattle/Animation/DA_ComboAttack.DA_ComboAttack"));
	if (ComboActionDataRef.Object)
	{
		ComboAttackData = ComboActionDataRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Game/ArenaBattle/Animation/AM_Character.AM_Character"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Game/ArenaBattle/Animation/AM_Dead.AM_Dead"));
	if (DeadMontageRef.Object)
	{ 
		DeadMontage = DeadMontageRef.Object;
	}

	//BBNPCData = AIControllerClass->
}

void AABCharacterNonPlayer::AttackHitCheck(AttackType AttackType)
{
}

void AABCharacterNonPlayer::ProcessComboCommand()
{
	Super::AAABCharacterBase::ProcessComboCommand();

}

void AABCharacterNonPlayer::Tick(float deltasec)
{
	Super::Tick(deltasec);
	TArray<AActor*> PerceivedActors;

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
	else
	{
		AABAIController* AIController = Cast<AABAIController>(GetController());
		if (AIController)
		{
			UE_LOG(LogTemp, Warning, TEXT("Null"));
			AIController->Seenplayer(SeenPawn);
		}
	}
}