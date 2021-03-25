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

void ASTEnemyController::BeginTurn(const TArray<class ASTCharacterBase*> InPlayersCharacters)
{
	PlayersCharacters = InPlayersCharacters;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASTEnemyController::PickTarget, 1.0f, false);
	GEngine->AddOnScreenDebugMessage(-1,1.f,FColor::Red, FString("Picking Target..."));
}
