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
	
	UE_LOG(LogTemp, Warning,TEXT("Enemy controller %s beginning turn."), *GetName());
	
	float CharIndex = FMath::RandRange(0, PlayersCharacters.Num() -1);

	UE_LOG(LogTemp, Warning, TEXT("ECHO ||||| %i"), PlayersCharacters.Num());
	for(ASTCharacterBase* Char : PlayersCharacters)
	{
		if(Char == nullptr)
			UE_LOG(LogTemp, Warning, TEXT("NULL ||||| %s"), *Char->GetName());
		UE_LOG(LogTemp, Warning, TEXT("ECHO ||||| %s"), *Char->GetName());
		UE_LOG(LogTemp, Warning, TEXT("%f"), Char->GetHealth());
		UE_LOG(LogTemp, Warning, TEXT("%s"), Char->IsPendingKillOrUnreachable() ? TEXT("true") : TEXT("false"));
		
	}
	
	SelectedCharacter->HandleTarget(FindLowestHealthValueTarget(), 0);
}
