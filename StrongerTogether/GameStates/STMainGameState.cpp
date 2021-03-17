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

void ASTMainGameState::StartCombat()
{
	switch(SelectedDelegateType)
	{
		case EDelegate::FCombatStarted:
		{
			CombatStarted.ExecuteIfBound();
			UE_LOG(LogTemp, Warning, TEXT("Executed base delegate"));
		}
		break;
		case EDelegate::FCombatStartedD:
		{
			CombatStartedDelegateD.ExecuteIfBound();
			UE_LOG(LogTemp, Warning, TEXT("Executed dynamic delegate"));
		}
		break;
		case EDelegate::FCombatStartedM:
		{
			CombatStartedDelegateM.Broadcast();
			UE_LOG(LogTemp, Warning, TEXT("Executed multicast delegate"));
		}
		break;
		case EDelegate::FCombatStartedDM:
		{
			CombatStartedDelegateDM.Broadcast();
			UE_LOG(LogTemp, Warning, TEXT("Executed dynamic multicast delegate"));
		}
		break;
	}
}
