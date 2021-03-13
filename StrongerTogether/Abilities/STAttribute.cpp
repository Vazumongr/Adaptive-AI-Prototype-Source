// Copyright Epic Games, Inc. All Rights Reserved.


#include "StrongerTogether/Abilities/STAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "StrongerTogether/Characters/STPartyCharacter.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

USTAttributeSet::USTAttributeSet()
	: Health(1.f)
	, MaxHealth(1.f)
	, Mana(0.f)
	, MaxMana(0.f)
	, AttackPower(1.0f)
	, DefensePower(1.0f)
	, Damage(0.0f)
{
}

#pragma region REPLICATEDSTUFF

void USTAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USTAttributeSet, Health);
	DOREPLIFETIME(USTAttributeSet, MaxHealth);
	DOREPLIFETIME(USTAttributeSet, Mana);
	DOREPLIFETIME(USTAttributeSet, MaxMana);
	DOREPLIFETIME(USTAttributeSet, AttackPower);
	DOREPLIFETIME(USTAttributeSet, DefensePower);
}

void USTAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet, Health, OldValue);
}

void USTAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet, MaxHealth, OldValue);
}

void USTAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet, Mana, OldValue);
}

void USTAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet, MaxMana, OldValue);
}

void USTAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet, AttackPower, OldValue);
}

void USTAttributeSet::OnRep_DefensePower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet, DefensePower, OldValue);
}

void USTAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet, Speed, OldValue);
}

#pragma endregion