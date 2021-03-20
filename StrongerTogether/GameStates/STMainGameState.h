// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "STMainGameState.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCombatStartedDM);

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE(FCombatStartedD);

DECLARE_MULTICAST_DELEGATE(FCombatStartedM);

DECLARE_DELEGATE(FCombatStarted);

UENUM()
enum class EDelegate : uint8
{
	FCombatStartedDM,
	FCombatStartedD,
	FCombatStartedM,
	FCombatStarted
};

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

	void PlayerTurnOver();

	FCombatStartedM CombatStartedDelegateM;
	
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
