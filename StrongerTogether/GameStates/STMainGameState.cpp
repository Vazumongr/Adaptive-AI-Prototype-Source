// Fill out your copyright notice in the Description page of Project Settings.


#include "STMainGameState.h"

#include "StrongerTogether/Managers/STTurnManager.h"

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

void ASTMainGameState::ReceivePlayerAnchor(ASTPlayerAnchor* InAnchor)
{
	if(InAnchor != nullptr)
	{
		PlayerAnchor = InAnchor;
		UE_LOG(LogTemp, Warning, TEXT("I have received the player anchor"));
	}
}
