// Fill out your copyright notice in the Description page of Project Settings.


#include "STPartyCharacter.h"

#include "StrongerTogether/Pawns/STAnchor.h"
#include "StrongerTogether/Abilities/STGameplayAbility.h"

// Sets default values
ASTPartyCharacter::ASTPartyCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FGuid MyID = FGuid::NewGuid();
	Name = MyID.ToString();
}

void ASTPartyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ASTPartyCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();

	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->RefreshAbilityActorInfo();
	}
}

void ASTPartyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASTPartyCharacter, CharacterLevel);
}

void ASTPartyCharacter::SetOwningAnchor(ASTAnchor* InAnchor)
{
	if(InAnchor != nullptr)
	{
		OwningAnchor = InAnchor;
		OwningAnchor->AnchorMoving.AddDynamic(this, &ASTPartyCharacter::StartMoving);
		OwningAnchor->AnchorStopping.AddDynamic(this, &ASTPartyCharacter::StopMoving);
	}
}

void ASTPartyCharacter::AddStartupGameplayAbilities()
{
	check(AbilitySystemComponent);

	if(!bAbilitiesInitialized)
	{
		for(TSubclassOf<USTGameplayAbility>& InitialAbility : InitialAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(InitialAbility, GetCharacterLevel(), INDEX_NONE, this));
		}
	}

	bAbilitiesInitialized = true;
	
}

float ASTPartyCharacter::GetHealth() const
{
	if(!AttributeSet)
		return 1.f;

	return AttributeSet->GetHealth();
}

float ASTPartyCharacter::GetMaxHealth() const
{
	if(!AttributeSet)
		return 1.f;

	return AttributeSet->GetMaxHealth();
}

float ASTPartyCharacter::GetMana() const
{
	if(!AttributeSet)
		return 1.f;

	return AttributeSet->GetMana();
}

float ASTPartyCharacter::GetMaxMana() const
{
	if(!AttributeSet)
		return 1.f;

	return AttributeSet->GetMaxMana();
}

bool ASTPartyCharacter::SetCharacterLevel(int32 NewLevel)
{
	if(CharacterLevel != NewLevel && NewLevel > 0)
	{
		CharacterLevel = NewLevel;
		return true;
	}
	return false;
}

// Called when the game starts or when spawned
void ASTPartyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

