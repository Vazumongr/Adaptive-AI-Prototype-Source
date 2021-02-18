// Copyright Epic Games, Inc. All Rights Reserved.

#include "StrongerTogether/Abilities/STAbilityTypes.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

bool FSTGameplayEffectContainerSpec::HasValidEffects() const
{
    return TargetGameplayEffectSpecs.Num() > 0;
}

bool FSTGameplayEffectContainerSpec::HasValidTargets() const
{
    return TargetData.Num() > 0;
}

void FSTGameplayEffectContainerSpec::AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors)
{
    for (const FHitResult& HitResult : HitResults)
    {
        FGameplayAbilityTargetData_SingleTargetHit* NewData = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
        TargetData.Add(NewData);
    }

    if (TargetActors.Num() > 0)
    {
        FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();
        NewData->TargetActorArray.Append(TargetActors);
        TargetData.Add(NewData);
    }
}