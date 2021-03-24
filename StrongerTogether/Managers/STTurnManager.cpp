// Copyright

#include "STTurnManager.h"

#include "StrongerTogether/Pawns/STAnchor.h"
#include "StrongerTogether/Pawns/STPlayerAnchor.h"
#include "StrongerTogether/Pawns/STCharacterBase.h"
#include "StrongerTogether/Characters/STEnemyCharacter.h"
#include "StrongerTogether/Controllers/STEnemyController.h"
#include "StrongerTogether/Controllers/STPlayerController.h"
#include "StrongerTogether/Widgets/STCharacterHUD.h"

void ASTTurnManager::BeginPlay()
{
	Super::BeginPlay();
}

void ASTTurnManager::Init()
{
}

void ASTTurnManager::SetCharacterTurn(bool bTurnValue)
{
	if(TurnCounter >= SortedCombatants.Num()) return;

	if(!IsValid(SortedCombatants[TurnCounter]))
	{
		SortedCombatants.RemoveAt(TurnCounter);
		if(TurnCounter >= SortedCombatants.Num())
		{
			TurnCounter = 0;
		}
	}
	
	SortedCombatants[TurnCounter]->bMyTurn = bTurnValue;
	if(ASTPlayerController* PlayerController = Cast<ASTPlayerController>(SortedCombatants[TurnCounter]->GetOwningAnchor()->GetController()))
	{
		PlayerController->bMyTurn = bTurnValue;
	}
	else if(ASTEnemyController* EnemyController = Cast<ASTEnemyController>(SortedCombatants[TurnCounter]->GetOwningAnchor()->GetController()))
	{
		EnemyController->bMyTurn = bTurnValue;
		if(bTurnValue == true)
		{
			EnemyController->SelectedCharacter = Cast<ASTEnemyCharacter>(SortedCombatants[TurnCounter]);
			EnemyController->BeginTurn(PlayerAnchor->PartyActors);
		}
	}
	if(CharacterHUD != nullptr)
		CharacterHUD->SetCharacterTurnText(SortedCombatants[TurnCounter]->Name);
}

void ASTTurnManager::CombatStarted()
{
	SetCombatOrder();
	TurnCounter = 0;
	SetCharacterTurn(true);
	
}

void ASTTurnManager::PlayerTurnOver()
{
	SetCharacterTurn(false);
	if(++TurnCounter > (SortedCombatants.Num() - 1))
	{
		TurnCounter = 0;
	}
	SetCharacterTurn(true);
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

void ASTTurnManager::SetCharacterHUDPtr(USTCharacterHUD* InHud)
{
	if(InHud != nullptr)
		CharacterHUD = InHud;
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
	ASTCharacterBase* key;
	int n = sizeof(SortedCombatants) / sizeof(SortedCombatants[0]);
	
	for(i = 1; i < SortedCombatants.Num(); i++)
	{
		key = SortedCombatants[i];
		j = i - 1;

		while(j >= 0 && SortedCombatants[j]->GetSpeed() < key->GetSpeed())
		{
			SortedCombatants[j + 1] = SortedCombatants[j];
			j = j - 1;
		}
		SortedCombatants[j + 1] = key;
	}
}

void ASTTurnManager::LogCombatants()
{
	for(const ASTCharacterBase* Char : SortedCombatants)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Char->Name.ToString());
	}
}


