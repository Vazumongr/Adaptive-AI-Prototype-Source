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
	TurnManager = GetWorld()->SpawnActor<ASTTurnManager>(TurnManagerClass);
	if(TurnManager != nullptr)
	{
		TurnManager->SetPlayerAnchorReference(PlayerAnchor);
	}
}

void ASTMainGameState::ReceivePlayer(ASTPlayerAnchor* InAnchor, APlayerController* InPlayerController)
{
	if(InAnchor != nullptr)
	{
		PlayerAnchor = InAnchor;
		PlayerController = Cast<ASTPlayerController>(InPlayerController);
		UE_LOG(LogTemp, Warning, TEXT("I have received the player anchor"));
	}
}

void ASTMainGameState::StartCombat(AActor* InAnchor)
{
	CombatStartedDelegateM.Broadcast();

	EnemyAnchor = Cast<ASTAnchor>(InAnchor);
	if(EnemyAnchor != nullptr)
	{
		EnemyController = Cast<ASTEnemyController>(EnemyAnchor->GetController());
		
		if(EnemyController != nullptr)
		{
			EnemyController->bMyTurn = false;
		}
	}

	if(PlayerController != nullptr)
	{
		PlayerController->bMyTurn = true;
	}
	
	if(PlayerAnchor != nullptr)
	{
		PlayerAnchor->PartyActors[0]->bMyTurn = true;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Executed multicast delegate"));
}
