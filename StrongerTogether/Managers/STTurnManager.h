// Copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"

#include "STTurnManager.generated.h"

UCLASS()
class STRONGERTOGETHER_API ASTTurnManager : public AInfo
{

	GENERATED_BODY()

	virtual void BeginPlay() override;

	void Init();


public:

	void CombatStarted();
	void PlayerTurnOver();
	
	void SetPlayerAnchorReference(class ASTPlayerAnchor* InAnchor);
	void SetEnemyAnchorReference(class ASTAnchor* EnemyAnchor);

private:

	void SetCombatOrder();
	void SortCombatants();
	void LogCombatants();
	void SetCharacterTurn(bool bTurnValue);
	//void SortCombatants(const TArray<class ASTCharacterBase*>& UnsortedCombatants);

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess))
	TArray<class ASTCharacterBase*> SortedCombatants;

	UPROPERTY()
	int8 TurnCounter;

	UPROPERTY()
	class ASTPlayerAnchor* PlayerAnchor;
	UPROPERTY()
	class ASTAnchor* EnemyAnchor;
	/*
	UPROPERTY()
	class ASTEnemyController* EnemyController;
	UPROPERTY()
	class ASTPlayerController* PlayerController;
	*/
};