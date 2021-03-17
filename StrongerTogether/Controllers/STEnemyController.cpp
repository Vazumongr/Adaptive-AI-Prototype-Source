// Copyright

#include "STEnemyController.h"

void ASTEnemyController::BeginPlay()
{
	Super::BeginPlay();
	bMyTurn = false;
}

void ASTEnemyController::Tick(float DeltaSeconds)
{
	if(bMyTurn) UE_LOG(LogTemp, Warning, TEXT("Enemies turn"));
}
