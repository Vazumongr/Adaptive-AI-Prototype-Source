// Copyright

#include "STEnemyController.h"

#include "StrongerTogether/Characters/STEnemyCharacter.h"

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
	ASTCharacterBase* LowestHealthTarget = FindLowestHealthValueTarget();
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this, LowestHealthTarget]
	{
		SelectedCharacter->HandleTarget(LowestHealthTarget, 0);
	});

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, false);
}

ASTCharacterBase* ASTEnemyController::FindLowestHealthValueTarget()
{
	int32 LowestHealthIndex = {0};
	for(int32 i = 0; i < PlayersCharacters.Num(); i++)
	{
		if(PlayersCharacters[i]->GetHealth() < PlayersCharacters[LowestHealthIndex]->GetHealth())
		{
			LowestHealthIndex = i;
		}
	}
	return PlayersCharacters[LowestHealthIndex];
}

ASTCharacterBase* ASTEnemyController::FindLowestHealthPercentageTarget()
{
	int32 LowestHealthIndex = {0};
	for(int32 i = 0; i < PlayersCharacters.Num(); i++)
	{
		if(PlayersCharacters[i]->GetHealthPercent() < PlayersCharacters[LowestHealthIndex]->GetHealthPercent())
		{
			LowestHealthIndex = i;
		}
	}
	return PlayersCharacters[LowestHealthIndex];
}

void ASTEnemyController::BeginTurn(const TArray<class ASTCharacterBase*> InPlayersCharacters)
{
	PlayersCharacters = InPlayersCharacters;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASTEnemyController::PickTarget, 1.0f, false);
}
