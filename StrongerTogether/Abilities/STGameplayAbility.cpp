// Copyright Epic Games, Inc. All Rights Reserved.

#include "StrongerTogether/Abilities/STGameplayAbility.h"

#include "StrongerTogether/Pawns/STCharacterBase.h"
#include "STAbilitySystemComponent.h"

USTGameplayAbility::USTGameplayAbility() {}

bool USTGameplayAbility::GetDamagingEffect()
{
	FGameplayEffectContextHandle Handle;
	AActor* OwningActor = GetOwningActorFromActorInfo();
	ASTCharacterBase* OwningCharacter = Cast<ASTCharacterBase>(OwningActor);
	if(OwningCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owning Character is NULL"));
		return false;
	}
	UAbilitySystemComponent* OwningASC = OwningCharacter->AbilitySystemComponent;
	if(OwningASC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owning ASC is NULL"));
		return false;
	}
	FGameplayEffectSpecHandle SpecHandle = OwningASC->MakeOutgoingSpec(GameplayEffects[0], 1, Handle);	// requires damage effect in slot 0
	if(SpecHandle.Data == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpecHandle.Data is NULL"));
		return false;
	}
	FGameplayEffectModifiedAttribute* ModifiedAttribute = SpecHandle.Data->GetModifiedAttribute(OwningCharacter->AttributeSet->GetHealthAttribute());
	if(ModifiedAttribute == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Modified Attribute is NULL"));
		return false;
	}
	const float DamageAmount = ModifiedAttribute->TotalMagnitude;
	UE_LOG(LogTemp, Warning, TEXT("Character has damaging ability dealing %f damage!"), DamageAmount);
	return true;
}

