// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AABCharacterBase.h"
#include "Interface/ABAnimationAttackInterface.h"
#include "Engine/StreamableManager.h"
#include "Perception/PawnSensingComponent.h"
#include "AI/ABAIController.h"
#include "ABCharacterNonPlayer.generated.h"

/**
 *
 */
 //DECLARE_DELEGATE(FOnNPCDead);

UCLASS(Config = ArenaBattle)
class ARENABATTLE_API AABCharacterNonPlayer : public AAABCharacterBase, public IABAnimationAttackInterface
{
	GENERATED_BODY()


	//FOnNPCDead OnNPCDead;

public:

	AABCharacterNonPlayer();

	virtual void AttackHitCheck(AttackType AttackType) override;

	virtual void ProcessComboCommand()override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void SetDead() override;

	virtual void PostInitializeComponents() override;

	void NPCMeshLoadCompleted();

	UFUNCTION()
	void OnSeePawn(APawn* SeenPawn);

protected:
	UPROPERTY(Config)
	TArray<FSoftObjectPath> NPCMeshes;

	TSharedPtr<FStreamableHandle> NPCMeshesHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UPawnSensingComponent* SensingPlayer;

	UBlackboardData* BBNPCData;

	TObjectPtr<class AAABCharacterPlayer> SeenPlayer;
};
