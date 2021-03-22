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
	if(bMyTurn) UE_LOG(LogTemp, Warning, TEXT("Enemies turn"));
}

void ASTEnemyController::BeginTurn(const TArray<class ASTCharacterBase*>& PlayersCharacters)
{
	UE_LOG(LogTemp, Warning,TEXT("Enemy controlling beginning turn. Selected character is %s"), *SelectedCharacter->Name.ToString());
	float CharIndex = FMath::RandRange(0, PlayersCharacters.Num() -1);
	UE_LOG(LogTemp, Warning, TEXT("I am targetting %s at random"), *PlayersCharacters[CharIndex]->Name.ToString());
	SelectedCharacter->HandleTarget(PlayersCharacters[CharIndex], 0);
}
