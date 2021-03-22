// Fill out your copyright notice in the Description page of Project Settings.


#include "STCharacterHUD.h"

#include "Components/TextBlock.h"
#include "Components/Border.h"

#include "StrongerTogether/Characters/STPartyCharacter.h"
#include "StrongerTogether/Controllers/STPlayerController.h"

bool USTCharacterHUD::Initialize()
{
    if(!Super::Initialize()) return false;

    if(AbilityOneBorder!= nullptr)
        AbilityOneBorder->OnMouseButtonDownEvent.BindUFunction(this, "UpdateOwnerAbilityIndexToZero");
    if(AbilityTwoBorder!= nullptr)
        AbilityTwoBorder->OnMouseButtonDownEvent.BindUFunction(this, "UpdateOwnerAbilityIndexToOne");
    if(AbilityThreeBorder!= nullptr)
        AbilityThreeBorder->OnMouseButtonDownEvent.BindUFunction(this, "UpdateOwnerAbilityIndexToTwo");

    return true;
}

void USTCharacterHUD::ClearHUD() const
{
    CharacterNameTextBlock->SetText(FText::FromString(""));
    AbilityOneTextBlock->SetText(FText::FromString(""));
    AbilityTwoTextBlock->SetText(FText::FromString(""));
    AbilityThreeTextBlock->SetText(FText::FromString(""));
    HealthTextBlock->SetText(FText::FromString(""));
    ManaTextBlock->SetText(FText::FromString(""));
}

void USTCharacterHUD::SetCharacterTurnText(const FName& CharName)
{
    CharacterTurnTextBlock->SetText(FText::FromName(CharName));
}

void USTCharacterHUD::UpdateOwnerAbilityIndexToZero() const
{
    UpdateController(0);
}

void USTCharacterHUD::UpdateOwnerAbilityIndexToOne() const
{
    UpdateController(1);
}

void USTCharacterHUD::UpdateOwnerAbilityIndexToTwo() const
{
    UpdateController(2);
}

void USTCharacterHUD::UpdateController(int32 AbilityIndex) const
{
    if(OwningController == nullptr) return;
    OwningController->PrimeAbility(AbilityIndex);
}

void USTCharacterHUD::Update(ASTPartyCharacter* InActor)
{
    if(InActor == nullptr) return;
    CharacterNameTextBlock->SetText(FText::FromName(InActor->Name));
    AbilityOneTextBlock->SetText(FText::FromString(InActor->AbilityOne));
    AbilityTwoTextBlock->SetText(FText::FromString(InActor->AbilityTwo));
    AbilityThreeTextBlock->SetText(FText::FromString(InActor->AbilityThree));
    HealthTextBlock->SetText(FText::FromString(FString::SanitizeFloat(InActor->GetHealth())));
    ManaTextBlock->SetText(FText::FromString(FString::SanitizeFloat(InActor->GetMana())));
}
