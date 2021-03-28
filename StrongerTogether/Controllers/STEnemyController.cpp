// Copyright

#include "STEnemyController.h"

#include "StrongerTogether/Characters/STEnemyCharacter.h"
#include "StrongerTogether/GameModes/STMainGameMode.h"
#include "StrongerTogether/GameStates/STMainGameState.h"
#include "StrongerTogether/Managers/STTurnManager.h"

void ASTEnemyController::BeginPlay()
{
	Super::BeginPlay();
	bMyTurn = false;
}

void ASTEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASTEnemyController::PickTarget()
{
	ASTCharacterBase* LowestHealthTarget = FindLowestHealthPercentageTarget();
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this, LowestHealthTarget]
	{
		SelectedCharacter->HandleTarget(LowestHealthTarget, 0);
		GEngine->AddOnScreenDebugMessage(-1,1.f,FColor::Red, FString("Attacked Target..."));
	});

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, false);
	GEngine->AddOnScreenDebugMessage(-1,1.f,FColor::Red, FString("Handling Target..."));
}

ASTCharacterBase* ASTEnemyController::FindLowestHealthValueTarget()
{
	int32 LowestHealthIndex = {0};
	bool bValChanged = false;
	for(int32 i = 0; i < PlayersCharacters.Num(); i++)
	{
		if(PlayersCharacters[i]->GetHealth() < PlayersCharacters[LowestHealthIndex]->GetHealth())
		{
			LowestHealthIndex = i;
		}
	}
	if(!bValChanged)	// If all at same health percentage, pick randomly
		LowestHealthIndex = FMath::RandRange(0, PlayersCharacters.Num() -1);
	return PlayersCharacters[LowestHealthIndex];
}

ASTCharacterBase* ASTEnemyController::FindLowestHealthPercentageTarget()
{
	int32 LowestHealthIndex = {0};
	bool bValChanged = false;
	for(int32 i = 0; i < PlayersCharacters.Num(); i++)
	{
		if(PlayersCharacters[i]->GetHealthPercent() < PlayersCharacters[LowestHealthIndex]->GetHealthPercent())
		{
			LowestHealthIndex = i;
			bValChanged = true;
		}
	}
	if(!bValChanged)	// If all at same health percentage, pick randomly
		LowestHealthIndex = FMath::RandRange(0, PlayersCharacters.Num() -1);
	return PlayersCharacters[LowestHealthIndex];
}

ASTCharacterBase* ASTEnemyController::FindKillableTarget()
{
	const float DamageAmount = SelectedCharacter->GetDamageAbility();
	TArray<ASTCharacterBase*> KillableTargets;
	const int32 LowestHealthIndex {0};
	
	for(int32 i = 0; i < PlayersCharacters.Num(); i++)
	{
		if(PlayersCharacters[i]->GetHealth() <= DamageAmount)
		{
			KillableTargets.Add(PlayersCharacters[i]);
		}
	}

	ASTMainGameState* GameState = Cast<ASTMainGameState>(GetWorld()->GetGameState());
	if(GameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameState is nullptr"));
		return nullptr;
	}
	ASTTurnManager* TurnManager = GameState->GetTurnManager();
	if(TurnManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TurnManager is nullptr"));
	}

	TArray<ASTCharacterBase*> TurnOrder;
	int32 Idx;
	
	TurnManager->GetTurnOrder(TurnOrder, Idx);
	UE_LOG(LogTemp, Warning, TEXT("First Fetch: %s"), *TurnOrder[0]->GetName());
	TurnOrder.RemoveAt(0);
	UE_LOG(LogTemp, Warning, TEXT("First Removal: %s"), *TurnOrder[0]->GetName());
	TurnManager->GetTurnOrder(TurnOrder, Idx);
	UE_LOG(LogTemp, Warning, TEXT("Second Fetch: %s"), *TurnOrder[0]->GetName());
	
	
	return PlayersCharacters[LowestHealthIndex];
}

void ASTEnemyController::BeginTurn(const TArray<class ASTCharacterBase*> InPlayersCharacters)
{
	PlayersCharacters = InPlayersCharacters;

	FindKillableTarget();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASTEnemyController::PickTarget, 1.0f, false);
	GEngine->AddOnScreenDebugMessage(-1,1.f,FColor::Red, FString("Picking Target..."));
}
