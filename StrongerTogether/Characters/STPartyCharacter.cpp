// Fill out your copyright notice in the Description page of Project Settings.


#include "STPartyCharacter.h"


#include "STEnemyCharacter.h"
#include "StrongerTogether/Pawns/STPlayerAnchor.h"


// Sets default values
ASTPartyCharacter::ASTPartyCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AllyClass = this->StaticClass();
	EnemyClass = ASTEnemyCharacter::StaticClass();
}


void ASTPartyCharacter::SetOwningAnchor(ASTAnchor* InAnchor)
{
	if(ASTPlayerAnchor* PlayerAnchor = Cast<ASTPlayerAnchor>(InAnchor))
	{
		OwningAnchor = InAnchor;
		PlayerAnchor->AnchorMoving.AddDynamic(this, &ASTPartyCharacter::StartMoving);
		PlayerAnchor->AnchorStopping.AddDynamic(this, &ASTPartyCharacter::StopMoving);
	}
}

void ASTPartyCharacter::HandleTarget2(AActor* TargetActor, int32 AbilityIndexToActivate)
{
	if(TargetActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("You called HandleTarget with a nullptr!"));
	}
	else
	{
		if(AbilityIndexToActivate > AbilitySpecHandles.Num() - 1 || AbilityIndexToActivate < 0)
		{
			UE_LOG(LogTemp, Error, TEXT("That ability is out of bounds!"));
		}
		UE_LOG(LogTemp, Warning, TEXT("You are telling me to use ability %i on target %s"), AbilityIndexToActivate, *TargetActor->GetName());

		// Check tags on ability
		FGameplayAbilitySpecHandle& AbilityToActivate = AbilitySpecHandles[AbilityIndexToActivate];
		UGameplayAbility* AbilityBeingActivated = AbilitySystemComponent->FindAbilitySpecFromHandle(AbilityToActivate)->Ability;
		FGameplayTagContainer& AbilitiesTags = AbilityBeingActivated->AbilityTags;
		
		if(Cast<ASTPartyCharacter>(TargetActor)) // ally
		{
			if(AbilitiesTags.HasTagExact(FGameplayTag::RequestGameplayTag(FName("Ability.Targets.Ally"))))
			{
				SetTarget(TargetActor);
				ActivateAbilityByIndex(AbilityIndexToActivate);
			}
		}
		else if(Cast<ASTEnemyCharacter>(TargetActor))
		{
			if(AbilitiesTags.HasTagExact(FGameplayTag::RequestGameplayTag(FName("Ability.Targets.Enemy"))))
			{
				SetTarget(TargetActor);
				ActivateAbilityByIndex(AbilityIndexToActivate);
			}
		}
	}
		
}
