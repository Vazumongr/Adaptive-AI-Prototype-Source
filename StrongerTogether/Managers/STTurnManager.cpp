// Copyright

#include "STTurnManager.h"

void ASTTurnManager::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("TURN MANAGER IS ALIVE"));
}

void ASTTurnManager::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("I have been init"));
}

void ASTTurnManager::SetPlayerAnchorReference(ASTPlayerAnchor* InAnchor)
{
	if(InAnchor != nullptr)
	{
		PlayerAnchor = InAnchor;
	}
}

void ASTTurnManager::SetEnemyAnchorReference(ASTAnchor* InAnchor)
{
	if(InAnchor != nullptr)
	{
		EnemyAnchor = InAnchor;
	}
}
