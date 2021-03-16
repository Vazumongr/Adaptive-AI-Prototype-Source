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

	
	void SetPlayerAnchorReference(class ASTPlayerAnchor* InAnchor);
	void SetEnemyAnchorReference(class ASTAnchor* EnemyAnchor);

private:
	UPROPERTY()
	class ASTPlayerAnchor* PlayerAnchor;
	UPROPERTY()
	class ASTAnchor* EnemyAnchor;
};