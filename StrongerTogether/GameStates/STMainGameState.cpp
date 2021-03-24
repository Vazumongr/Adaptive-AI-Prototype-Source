// Fill out your copyright notice in the Description page of Project Settings.


#include "STMainGameState.h"

#include "StrongerTogether/Managers/STTurnManager.h"
#include "StrongerTogether/Controllers/STPlayerController.h"
#include "StrongerTogether/Controllers/STEnemyController.h"
#include "StrongerTogether/Pawns/STPlayerAnchor.h"
#include "StrongerTogether/Pawns/STCharacterBase.h"


ASTMainGameState::ASTMainGameState()
{
	TurnManagerClass = ASTTurnManager::StaticClass();
}

void ASTMainGameState::Init()
{
	if(TurnManager == nullptr)
	{
		TurnManager = GetWorld()->SpawnActor<ASTTurnManager>(TurnManagerClass);
	}
	if(TurnManager != nullptr)
	{
		TurnManager->SetPlayerAnchorReference(PlayerAnchor);
		CombatStartedDelegateM.AddUObject(TurnManager, &ASTTurnManager::CombatStarted);
	}
}

void ASTMainGameState::ReceivePlayer(ASTPlayerAnchor* InAnchor, APlayerController* InPlayerController)
{
	if(InAnchor != nullptr)
	{
		PlayerAnchor = InAnchor;
		PlayerController = Cast<ASTPlayerController>(InPlayerController);
	}
}

void ASTMainGameState::StartCombat(AActor* InAnchor)
{
	if(InAnchor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameState::StartCombat was called with invalid enemy anchor!"));
		return;
	}
	EnemyAnchor = Cast<ASTAnchor>(InAnchor);

	if(EnemyAnchor != nullptr && PlayerAnchor != nullptr)
	{
		TurnManager->SetPlayerAnchorReference(PlayerAnchor);
		TurnManager->SetEnemyAnchorReference(EnemyAnchor);
		CombatStartedDelegateM.Broadcast();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("GameState::StartCombat was called with invalid enemy or player anchor!"));
}

void ASTMainGameState::EndCombat(AActor* InAnchor)
{
	if(InAnchor != nullptr)
	{
		CombatEndedDelegateM.Broadcast();
	}
}

void ASTMainGameState::PlayerTurnOver()
{
	TurnManager->PlayerTurnOver();
}
