// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "STAnchor.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnchorMoving);

UCLASS()
class STRONGERTOGETHER_API ASTAnchor : public APawn
{
	GENERATED_BODY()

public:

#pragma region FUNCTIONS
	// Sets default values for this pawn's properties
	ASTAnchor();

	virtual void Tick(float DeltaSeconds) override;

	void SpawnPartyCharacter();
	void ArrangeParty();

	void AddPartyCharacter(AActor* InActor);
	void RemovePartyCharacter(AActor* InActor);

	void Advance(FVector NewLocation);
	
#pragma endregion 

#pragma region VARIABLES
	FAnchorMoving AnchorMoving;
	FAnchorMoving AnchorStopping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> PartyActors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSubclassOf<class ASTPartyCharacter> CharactersClass;

	bool bIsMoving = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PartyOffset = 50.f;

	TArray<float> Offsets;

	bool bMoveForward = false;

	FVector TargetLocation;
#pragma endregion
};
