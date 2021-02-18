// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "StrongerTogether/StrongerTogether.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "StrongerTogether/Abilities/STAbilityTypes.h"
#include "STTargetType.generated.h"

class ASTPartyCharacter;
class AActor;
struct FGameplayEventData;

/**
 * Class that is used to determine targeting for abilities
 * It is meant to be blueprinted to run target logic
 * This does not subclass GameplayAbilityTargetActor because this class is never instanced into the world
 * This can be used as a basis for a game-specific targeting blueprint
 * If your targeting is more complicated you may need to instance into the world once or as a pooled actor
 */
UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class STRONGERTOGETHER_API USTTargetType : public UObject
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	USTTargetType() {}

	/** Called to determine targets to apply gameplay effects to */
	UFUNCTION(BlueprintNativeEvent)
	void GetTargets(ASTPartyCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
};

/** Trivial target type that uses the owner */
UCLASS(NotBlueprintable)
class STRONGERTOGETHER_API USTTargetType_UseOwner : public USTTargetType
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	USTTargetType_UseOwner() {}

	/** Uses the passed in event data */
	virtual void GetTargets_Implementation(ASTPartyCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};

/** Trivial target type that pulls the target out of the event data */
UCLASS(NotBlueprintable)
class STRONGERTOGETHER_API USTTargetType_UseEventData : public USTTargetType
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	USTTargetType_UseEventData() {}

	/** Uses the passed in event data */
	virtual void GetTargets_Implementation(ASTPartyCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};
