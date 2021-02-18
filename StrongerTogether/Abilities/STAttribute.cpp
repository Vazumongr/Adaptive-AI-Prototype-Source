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

#pragma endregion


/* //dont need
void USTAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void USTAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// This is called whenever attributes change, so for max health/mana we want to scale the current totals to match
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		AdjustAttributeForMaxChange(Mana, MaxMana, NewValue, GetManaAttribute());
	}
}

*/