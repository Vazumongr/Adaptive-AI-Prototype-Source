// Copyright Epic Games, Inc. All Rights Reserved.

#include "StrongerTogether/Abilities/STGameplayAbility.h"

#include "StrongerTogether/Pawns/STCharacterBase.h"
#include "STAbilitySystemComponent.h"

USTGameplayAbility::USTGameplayAbility() {}

float USTGameplayAbility::GetDamagingEffect(ASTCharacterBase* OwningCharacter)
{
	FGameplayEffectContextHandle Handle;

	if(OwningCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owning Character is NULL"));
		return 0;
	}
	
	UAbilitySystemComponent* OwningASC = OwningCharacter->AbilitySystemComponent;
	if(OwningASC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owning ASC is NULL"));
		return 0;
	}
	
	FGameplayEffectSpecHandle SpecHandle = OwningASC->MakeOutgoingSpec(GameplayEffects[0], 1, Handle);	// requires damage effect in slot 0
	if(SpecHandle.Data == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpecHandle.Data is NULL"));
		return 0;
	}
	
	SpecHandle.Data->CalculateModifierMagnitudes();
	
	const float DamageAmount = SpecHandle.Data->GetModifierMagnitude(0,true);
	
	UE_LOG(LogTemp, Warning, TEXT("Character has damaging ability dealing %f damage!"), DamageAmount);
	
	return DamageAmount;
}

