// Copyright

#include "STTurnManager.h"

#include "StrongerTogether/Pawns/STAnchor.h"
#include "StrongerTogether/Pawns/STPlayerAnchor.h"
#include "StrongerTogether/Pawns/STCharacterBase.h"
#include "StrongerTogether/Controllers/STEnemyController.h"
#include "StrongerTogether/Controllers/STPlayerController.h"

void ASTTurnManager::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("TURN MANAGER IS ALIVE"));
}

void ASTTurnManager::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("I have been init"));
}

void ASTTurnManager::CombatStarted()
{
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
	SetCombatOrder();
}

void ASTTurnManager::PlayerTurnOver()
{
	if(PlayerController != nullptr)
	{
		PlayerController->bMyTurn = false;
	}
	
	if(PlayerAnchor != nullptr)
	{
		PlayerAnchor->PartyActors[0]->bMyTurn = false;
	}

	if(EnemyAnchor != nullptr)
	{
		EnemyController = Cast<ASTEnemyController>(EnemyAnchor->GetController());

		EnemyAnchor->PartyActors[0]->bMyTurn = true;
		
		if(EnemyController != nullptr)
		{
			EnemyController->bMyTurn = true;
		}
	}
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

void ASTTurnManager::SetCombatOrder()
{
	TArray<ASTCharacterBase*> UnsortedCombatants;
	if(PlayerAnchor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sorting combatants failed. PlayerAnchor is null"));
		return;
	}
	if(EnemyAnchor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sorting combatants failed. EnemyAnchor is null"));
		return;
	}
	SortedCombatants.Empty();
	SortedCombatants.Append(PlayerAnchor->GetParty());
	SortedCombatants.Append(EnemyAnchor->GetParty());
	LogCombatants();
	SortCombatants();
	LogCombatants();
	
}

void ASTTurnManager::SortCombatants()
{
	int i, j;
	float key;
	int n = sizeof(SortedCombatants) / sizeof(SortedCombatants[0]);
	UE_LOG(LogTemp, Warning, TEXT("n is %i and Num() is %i"), n, SortedCombatants.Num());
	UE_LOG(LogTemp, Warning, TEXT("sizeof(SortedCombatants) is %i and sizeof(SortedCombatants[0]) is %i"), sizeof(SortedCombatants), sizeof(SortedCombatants[2]));
	for(i = 1; i < n; i++)
	{
		key = SortedCombatants[i]->GetSpeed();
		j = i - 1;

		while(j >= 0 && SortedCombatants[j]->GetSpeed() > key)
		{
			SortedCombatants[j + 1] = SortedCombatants[j];
			j = j - 1;
		}
		SortedCombatants[j + 1] = SortedCombatants[i];
	}
}

void ASTTurnManager::LogCombatants()
{
	for(const ASTCharacterBase* Char : SortedCombatants)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Char->Name.ToString());
	}
}


