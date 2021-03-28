// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Abilities/GameplayAbility.h"


#include "STGameplayAbility.generated.h"

/**
* Subclass of ability blueprint type with game-specific data
* This class uses GameplayEffectContainers to allow easier execution of gameplay effects based on a triggering tag
* Most games will need to implement a subclass to support their game-specific code
*/
UCLASS()
class STRONGERTOGETHER_API USTGameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()

    public:
    // Constructor and overrides
    USTGameplayAbility();

    bool GetDamagingEffect();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Abilities")
    TArray<TSubclassOf<class UGameplayEffect>> GameplayEffects;
};