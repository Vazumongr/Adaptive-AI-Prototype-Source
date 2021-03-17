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

public:
	bool bMyTurn;
	
};
