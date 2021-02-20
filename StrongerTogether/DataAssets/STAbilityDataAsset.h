// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StrongerTogether/Abilities/STGameplayAbility.h"

#include "STAbilityDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class STRONGERTOGETHER_API USTAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<USTGameplayAbility>	GameplayAbilityClass;
	UPROPERTY(EditAnywhere)
	FString AbilityName;
	UPROPERTY(EditAnywhere)
	FString AbilityDescription;
	
};
