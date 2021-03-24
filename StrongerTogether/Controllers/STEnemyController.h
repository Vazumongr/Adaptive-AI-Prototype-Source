// Copyright

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STEnemyController.generated.h"

UCLASS()
class STRONGERTOGETHER_API ASTEnemyController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void PickTarget();
	void PickAbility();
	void AttackTargetWithAbility();
	
	class ASTCharacterBase* FindLowestHealthValueTarget();
	class ASTCharacterBase* FindLowestHealthPercentageTarget();

	UPROPERTY()
	TArray<class ASTCharacterBase*> PlayersCharacters;

	FTimerHandle TimerHandle;

public:

	void BeginTurn(const TArray<class ASTCharacterBase*> InPlayersCharacters);
	
	UPROPERTY(VisibleAnywhere)
	bool bMyTurn;

	
	UPROPERTY(VisibleAnywhere)
	class ASTEnemyCharacter* SelectedCharacter;
	
};
