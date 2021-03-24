// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "STMainGameState.generated.h"

DECLARE_MULTICAST_DELEGATE(FCombatStartedM);
DECLARE_MULTICAST_DELEGATE(FCombatEndedM);

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

	void ReceivePlayer(class ASTPlayerAnchor* InAnchor, class APlayerController* InPlayerController);

	void StartCombat(AActor* EnemyAnchor);
	void EndCombat(AActor* InAnchor);

	void PlayerTurnOver();

	FORCEINLINE class ASTTurnManager* GetTurnManager() { return TurnManager; }

	FCombatStartedM CombatStartedDelegateM;
	FCombatEndedM CombatEndedDelegateM;
	
private:
	UPROPERTY()
	TSubclassOf<class ASTTurnManager> TurnManagerClass;

	UPROPERTY()
	class ASTTurnManager* TurnManager;
	UPROPERTY()
	class ASTPlayerAnchor* PlayerAnchor;
	UPROPERTY()
	class ASTAnchor* EnemyAnchor;
	UPROPERTY()
	class ASTPlayerController* PlayerController;
	UPROPERTY()
	class ASTEnemyController* EnemyController;

public:
	FORCEINLINE const class ASTAnchor* GetEnemyAnchor() { return EnemyAnchor; }
	FORCEINLINE const class ASTPlayerAnchor* GetPlayerAnchor() { return PlayerAnchor; }
	
};
