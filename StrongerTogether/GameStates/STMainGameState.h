// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "STMainGameState.generated.h"

/**
 * 
 */
UCLASS()
class STRONGERTOGETHER_API ASTMainGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASTMainGameState();

	void Init();

	void ReceivePlayerAnchor(class ASTPlayerAnchor* InAnchor);
	
private:
	UPROPERTY()
	TSubclassOf<class ASTTurnManager> TurnManagerClass;

	UPROPERTY()
	class ASTTurnManager* TurnManager;
	UPROPERTY()
	class ASTPlayerAnchor* PlayerAnchor;
	
};
