// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "STAnchor.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnchorMoving);	//Player Only

UCLASS()
class STRONGERTOGETHER_API ASTAnchor : public APawn
{
	GENERATED_BODY()

public:

#pragma region FUNCTIONS
	// Sets default values for this pawn's properties
	ASTAnchor();

	virtual void SpawnPartyCharacter();	// Override for player
	void ArrangeParty();

	virtual void BeginPlay() override;

	void AddPartyCharacter(class ASTCharacterBase* InActor);
	void RemovePartyCharacter(class ASTCharacterBase* InActor);
	
#pragma endregion 

#pragma region VARIABLES

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class ASTCharacterBase*> PartyActors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<TSubclassOf<class ASTCharacterBase>> CharactersClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PartyOffset = 50.f;

	TArray<float> Offsets;

	bool bInCombat;
#pragma endregion

protected:
	UFUNCTION()
	void CombatStarted();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	class UBoxComponent* BoxCollider;

	UPROPERTY()
	class ASTMainGameState* GameState;
};
