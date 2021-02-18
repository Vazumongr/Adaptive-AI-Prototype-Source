// Copyright Epic Games, Inc. All Rights Reserved.

#include "StrongerTogether/Abilities/STTargetType.h"
#include "StrongerTogether/Abilities/STGameplayAbility.h"
#include "StrongerTogether/Characters/STPartyCharacter.h"

void USTTargetType::GetTargets_Implementation(ASTPartyCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
    return;
}

void USTTargetType_UseOwner::GetTargets_Implementation(ASTPartyCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
    OutActors.Add(TargetingCharacter);
}

void USTTargetType_UseEventData::GetTargets_Implementation(ASTPartyCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
    const FHitResult* FoundHitResult = EventData.ContextHandle.GetHitResult();
    if (FoundHitResult)
    {
        OutHitResults.Add(*FoundHitResult);
    }
    else if (EventData.Target)
    {
        OutActors.Add(const_cast<AActor*>(EventData.Target));
    }
}