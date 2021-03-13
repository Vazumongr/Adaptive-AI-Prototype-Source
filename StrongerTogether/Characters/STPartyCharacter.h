// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrongerTogether/Pawns/STCharacterBase.h"

#include "STPartyCharacter.generated.h"

UCLASS()
class STRONGERTOGETHER_API ASTPartyCharacter : public ASTCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASTPartyCharacter();
	
	virtual void SetOwningAnchor(class ASTAnchor* InAnchor) override;

	void HandleTarget(AActor* TargetActor, int32 AbilityToActivate);

	UFUNCTION(BlueprintImplementableEvent)
    void StartMoving();

	UFUNCTION(BlueprintImplementableEvent)
    void StopMoving();
};
